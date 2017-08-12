#include "ethercat_init.h"
#include "speed_planning.h"

unsigned int ec_state=1; //servo motor state machine parameter
bool ethercat_state = 0;
uint16_t ESTUN_00_ctrlwd;//6040
uint16_t ESTUN_00_statwd;//6041
int8_t   ESTUN_00_modop;//6060
int8_t   ESTUN_00_modds;//6061
int32_t ESTUN_00_tarvel;//60ff
int32_t ESTUN_00_actvel;//606c
int32_t ESTUN_00_tarpos;//607a
int32_t ESTUN_00_actpos;//6064
uint32_t ESTUN_00_provel;//6081
uint32_t ESTUN_00_endvel;//6082
uint32_t ESTUN_00_proacc;//6083
uint32_t ESTUN_00_prodec;//6084

uint16_t ESTUN_01_ctrlwd;
uint16_t ESTUN_01_statwd;
int8_t   ESTUN_01_modop;
int8_t   ESTUN_01_modds;
int32_t ESTUN_01_tarvel;
int32_t ESTUN_01_actvel;
int32_t ESTUN_01_tarpos;
int32_t ESTUN_01_actpos;
uint32_t ESTUN_01_provel;
uint32_t ESTUN_01_endvel;
uint32_t ESTUN_01_proacc;
uint32_t ESTUN_01_prodec;

int32_t ESTUN_speed=0;





/*****************************************************************************/
//SUPPOSING THAT WE HAD A CONFIGURATION IN HAND, WE CAN SIMPLY INCLUDE IT IN THE
//SOURCE, LIKE THIS
#if PRECONFIGURE_PDOS

/* Master 0, Slave 0, "ESTUN ProNet"
 * Vendor ID:       0x0000060a
 * Product code:    0x00000001
 * Revision number: 0x00000001
 */
ec_pdo_entry_info_t ESTUN_00_pdo_entries[] = {
    {0x6040, 0x00, 16},
    {0x60ff, 0x00, 32},
    {0x6060, 0x00, 8},
    {0x607a, 0x00, 32},
    {0x6081, 0x00, 32},
    {0x6082, 0x00, 32},
    {0x6083, 0x00, 32},
    {0x6084, 0x00, 32},
    {0x6041, 0x00, 16},
    {0x606c, 0x00, 32},
    {0x6061, 0x00, 8},
    {0x6064, 0x00, 32},
};

ec_pdo_info_t ESTUN_00_pdos[] = {
    {0x1600, 8, ESTUN_00_pdo_entries + 0},
    {0x1a00, 4, ESTUN_00_pdo_entries + 8},
};

ec_sync_info_t ESTUN_00_syncs[] = {
    {0, EC_DIR_OUTPUT, 0, NULL, EC_WD_DISABLE},
    {1, EC_DIR_INPUT, 0, NULL, EC_WD_DISABLE},
    {2, EC_DIR_OUTPUT, 1, ESTUN_00_pdos + 0, EC_WD_ENABLE},
    {3, EC_DIR_INPUT, 1, ESTUN_00_pdos + 1, EC_WD_DISABLE},
    {0xff}
};

/* Master 0, Slave 1, "ESTUN ProNet"
 * Vendor ID:       0x0000060a
 * Product code:    0x00000001
 * Revision number: 0x00000001
 */
ec_pdo_entry_info_t ESTUN_01_pdo_entries[] = {
    {0x6040, 0x00, 16},
    {0x60ff, 0x00, 32},
    {0x6060, 0x00, 8},
    {0x607a, 0x00, 32},
    {0x6081, 0x00, 32},
    {0x6082, 0x00, 32},
    {0x6083, 0x00, 32},
    {0x6084, 0x00, 32},
    {0x6041, 0x00, 16},
    {0x606c, 0x00, 32},
    {0x6061, 0x00, 8},
    {0x6064, 0x00, 32},
};

ec_pdo_info_t ESTUN_01_pdos[] = {
    {0x1600, 8, ESTUN_01_pdo_entries + 0},
    {0x1a00, 4, ESTUN_01_pdo_entries + 8},
};

ec_sync_info_t ESTUN_01_syncs[] = {
    {0, EC_DIR_OUTPUT, 0, NULL, EC_WD_DISABLE},
    {1, EC_DIR_INPUT, 0, NULL, EC_WD_DISABLE},
    {2, EC_DIR_OUTPUT, 1, ESTUN_01_pdos + 0, EC_WD_ENABLE},
    {3, EC_DIR_INPUT, 1, ESTUN_01_pdos + 1, EC_WD_DISABLE},
    {0xff}
};

#endif

/*****************************************************************************/
void check_domain1_state(void)
{
    ec_domain_state_t ds;
    ecrt_domain_state(domain1, &ds);
    #if 1
    if (ds.working_counter != domain1_state.working_counter)
    printf("Domain1: WC %u.\n", ds.working_counter);
    if (ds.wc_state != domain1_state.wc_state)
    printf("Domain1: State %u.\n", ds.wc_state);
    #endif
    domain1_state = ds;
}
/*****************************************************************************/
void check_master_state(void)
{
    ec_master_state_t ms;
    ecrt_master_state(master, &ms);
    if (ms.slaves_responding != master_state.slaves_responding)
    printf("%u slave(s).\n", ms.slaves_responding);
    if (ms.al_states != master_state.al_states)
    printf("AL states: 0x%02X.\n", ms.al_states);
    if (ms.link_up != master_state.link_up)
    printf("Link is %s.\n", ms.link_up ? "up" : "down");
    master_state = ms;
}
/*****************************************************************************/
void check_slave_config_states()
{
    ec_slave_config_state_t s;
    ecrt_slave_config_state(sc_estun_00, &s);
    if (slaves_up < 1 && s.al_state != 0x08) {
    //printf("DigOut: State 0x%02X.\n", s.al_state);
    }
    if (slaves_up < 1 && s.al_state == 0x08) {
    slaves_up = 1;
    }
    sc_estun_00_state=s;

    ecrt_slave_config_state(sc_estun_01, &s);
    if (slaves_up < 2 && s.al_state != 0x08) {
    //printf("DigOut: State 0x%02X.\n", s.al_state);
    }
    if (slaves_up < 2 && s.al_state == 0x08) {
    slaves_up = 2;
    }
    sc_estun_01_state=s;
    printf("sc_estun_00_state 0x%02X.\n", sc_estun_00_state.al_state);
    printf("sc_estun_01_state 0x%02X.\n", sc_estun_01_state.al_state);
    printf("sc_estun_01_state 0x%01X.\n", sc_estun_01_state.online);
    printf("sc_estun_01_state 0x%01X.\n", sc_estun_01_state.operational);
}
/*****************************************************************************/
int EtherCAT_comm_int(void)
{
    unsigned int j,op_flag;
    unsigned int ctrl_flag=1;
    ec_slave_config_t *sc;
    ec_master_state_t ms;
    //FIRST, REQUEST A MASTER INSTANCE
    master = ecrt_request_master(0);
    if (!master)
    {
        fprintf(stderr, "Unable to get requested master.\n");
        return -1;
    }
    //THEN, CREATE A DOMAIN,at least one domain is needed.
    domain1 = ecrt_master_create_domain(master);
    if (!domain1)
    {
        fprintf(stderr, "Unable to create process data domain.\n");
        return -1;
    }
    #if CONFIGURE_PDOS
    printf("Configuring PDOs...\n");

    #endif

    //EITHER CONFIGURE THE PDOS AT RUNTIME (AS ABOVE),OR DO IT WITH THE PRECONFIGURED
    //INFO (AS BELOW)
    // Create configuration for the slaves

    if (!(sc_estun_00 = ecrt_master_slave_config(
              master, ESTUN_00_Pos, ESTUN_00))) {
        fprintf(stderr, "Failed to get slave ESTUN_00 configuration.\n");
        return -1;
    }
    if (ecrt_slave_config_pdos(sc_estun_00, EC_END, ESTUN_00_syncs)) {
        fprintf(stderr, "Failed to configure ESTUN_00 PDOs.\n");
        return -1;
    }

    if (!(sc_estun_01 = ecrt_master_slave_config(
              master, ESTUN_01_Pos, ESTUN_01))) {
        fprintf(stderr, "Failed to get slave ESTUN_01 configuration.\n");
        return -1;
    }
    if (ecrt_slave_config_pdos(sc_estun_01, EC_END, ESTUN_01_syncs)) {
        fprintf(stderr, "Failed to configure ESTUN_01 PDOs.\n");
        return -1;
    }
   //ecrt_slave_config_sdo8(sc_estun_00,0x6060,0,3);


    //  register PDO entry for domains.
    if (ecrt_domain_reg_pdo_entry_list(domain1, domain1_regs)) {
        fprintf(stderr, "PDO entry registration failed!\n");
        return -1;
    }
    //the configure of master,slaves,domains have already done!
    //ACTIVATE THE MASTER. DO NOT APPLY ANY CONFIGURATION AFTER THIS, IT WON'T WORK

    printf("Activating master...");
    if (ecrt_master_activate(master)) {
        fprintf(stderr,"activation failed.\n");
        return -1;
    }
    printf("ok!\n");

    //INITIALIZE THE PROCESS DOMAIN MEMORY (FOR USER-SPACE APPS)

    if (!(domain1_pd = ecrt_domain_data(domain1))) {
        fprintf(stderr,"Domain data initialization failed.\n");
        return -1;
    }

    printf("Domain data registered ok.\n");
    check_master_state();
    check_domain1_state();
    op_flag = 0;


    //ONCE THE MASTER IS ACTIVATED, THE APP IS IN CHARGE OF EXCHANGING DATA THROUGH
    //EXPLICIT CALLS TO THE ECRT LIBRARY (DONE IN THE IDLE STATE BY THE MASTER)
    #if 1
    //for (j=0;j<512;j++)
    while(ec_state)
    {
    ecrt_master_receive(master); //RECEIVE A FRAME
    ecrt_domain_process(domain1);// DETERMINE THE DATAGRAM STATES
    //check_slave_config_states();
    if (!op_flag) {
    check_domain1_state();
    }
    //printf(" data op_flag: %x\n", op_flag);
    #if 0
    if (slaves_up == 1 && !op_flag) {
    printf("All slaves reached OP state at %d cycles.\n", j);
    op_flag = 1;
    }
    #endif
    if (domain1_state.wc_state == EC_WC_COMPLETE && !op_flag) {
    printf("Domain is up at %d cycles.\n", j);
    op_flag = 1;
    }
    ethercat_state = 1;

    chassis_upload_ethercat();

    chassis_download_ethercat();

    if(op_flag&&ctrl_flag)
    {
        ctrl_flag=0;
    }

    // send process data
    ecrt_domain_queue(domain1); //MARK THE DOMAIN DATA AS READY FOR EXCHANGE
    ecrt_master_send(master); //SEND ALL QUEUED DATAGRAMS
    //printf("continue working.\n");
    usleep(50);
    }
    //dummy to keep abrt from seeing the last datagram (which won't match)
    ecrt_master_receive(master);
    ecrt_domain_process(domain1);
    #endif
    printf("...Done. Releasing the master!\n");
    ecrt_release_master(master); //RELEASE THE MASTER INSTANCE

    return 0;
}
/****************************************************************************/
void *EtherCAT_comm(void *arg)
{
    int rtn_ethercat_comm_int = -1;
    while(rtn_ethercat_comm_int < 0)
    {
        rtn_ethercat_comm_int=EtherCAT_comm_int();
        sleep(10);
    }

}

/*get info*/
void chassis_upload_ethercat()
{
    chassis.motorBL.statwd = EC_READ_U16(domain1_pd + off_estun_00_statwd);
    chassis.motorBL.ctrlwd = EC_READ_U16(domain1_pd + off_estun_00_ctrlwd);
    chassis.motorBL.modds  = EC_READ_U8(domain1_pd + off_estun_00_modds);
    chassis.motorBL.actvel = EC_READ_S32(domain1_pd + off_estun_00_actvel);
    chassis.motorBL.actpos = EC_READ_S32(domain1_pd + off_estun_00_actpos);

    chassis.motorFL.statwd = EC_READ_U16(domain1_pd + off_estun_01_statwd);
    chassis.motorFL.ctrlwd = EC_READ_U16(domain1_pd + off_estun_01_ctrlwd);
    chassis.motorFL.modds  = EC_READ_U8(domain1_pd + off_estun_01_modds);
    chassis.motorFL.actvel = EC_READ_S32(domain1_pd + off_estun_01_actvel);
    chassis.motorFL.actpos = EC_READ_S32(domain1_pd + off_estun_01_actpos);
}

/*put info*/
void chassis_download_ethercat()
{
    //ESTUN_00_ctrlwd = chassis.motorBL.ctrlwd;
    ESTUN_00_ctrlwd =coe_state_machine(chassis.motorBL.statwd,chassis.motorBL.ctrlwd,chassis.motorBL.modds);
    ESTUN_00_modop  = chassis.motorBL.modop;
    ESTUN_00_tarvel = chassis.motorBL.tarvel;
    ESTUN_00_tarpos = chassis.motorBL.tarpos;
    ESTUN_00_provel = chassis.motorBL.provel;
    ESTUN_00_endvel = chassis.motorBL.endvel;
    ESTUN_00_proacc = chassis.motorBL.proacc;
    ESTUN_00_prodec = chassis.motorBL.prodec;

    EC_WRITE_U8(domain1_pd  + off_estun_00_modop,ESTUN_00_modop);
    EC_WRITE_U16(domain1_pd + off_estun_00_ctrlwd,ESTUN_00_ctrlwd);
    EC_WRITE_S32(domain1_pd + off_estun_00_tarvel, ESTUN_00_tarvel);
    EC_WRITE_S32(domain1_pd + off_estun_00_tarpos, ESTUN_00_tarpos);
    EC_WRITE_U32(domain1_pd + off_estun_00_provel, ESTUN_00_provel);
    EC_WRITE_U32(domain1_pd + off_estun_00_endvel, ESTUN_00_endvel);
    EC_WRITE_U32(domain1_pd + off_estun_00_proacc, ESTUN_00_proacc);
    EC_WRITE_U32(domain1_pd + off_estun_00_prodec, ESTUN_00_prodec);

    //ESTUN_01_ctrlwd = chassis.motorFL.ctrlwd;
    ESTUN_01_ctrlwd =coe_state_machine(chassis.motorFL.statwd,chassis.motorFL.ctrlwd,chassis.motorFL.modds);
    ESTUN_01_modop  = chassis.motorFL.modop;
    ESTUN_01_tarvel = chassis.motorFL.tarvel;
    ESTUN_01_tarpos = chassis.motorFL.tarpos;
    ESTUN_01_provel = chassis.motorFL.provel;
    ESTUN_01_endvel = chassis.motorFL.endvel;
    ESTUN_01_proacc = chassis.motorFL.proacc;
    ESTUN_01_prodec = chassis.motorFL.prodec;

    EC_WRITE_U8(domain1_pd  + off_estun_01_modop,ESTUN_01_modop);
    EC_WRITE_U16(domain1_pd + off_estun_01_ctrlwd,ESTUN_01_ctrlwd);
    EC_WRITE_S32(domain1_pd + off_estun_01_tarvel, ESTUN_01_tarvel);
    EC_WRITE_S32(domain1_pd + off_estun_01_tarpos, ESTUN_01_tarpos);
    EC_WRITE_U32(domain1_pd + off_estun_01_provel, ESTUN_01_provel);
    EC_WRITE_U32(domain1_pd + off_estun_01_endvel, ESTUN_01_endvel);
    EC_WRITE_U32(domain1_pd + off_estun_01_proacc, ESTUN_01_proacc);
    EC_WRITE_U32(domain1_pd + off_estun_01_prodec, ESTUN_01_prodec);

}

CoEstate coe_state_turn(uint16_t statewd)
{
    if(((statewd&0x004F)^0x0000)==0)       return coe_not_ready;
    else if (((statewd&0x004F)^0x0040)==0) return switch_disable;
    else if (((statewd&0x006F)^0x0021)==0) return ready_switch;
    else if (((statewd&0x006F)^0x0023)==0) return switch_on;
    else if (((statewd&0x006F)^0x0027)==0) return operation_enable;
    else if (((statewd&0x006F)^0x0007)==0) return quick_stop;
    else if (((statewd&0x004F)^0x000F)==0) return fault_reaction;
    else if (((statewd&0x004F)^0x0008)==0) return coe_fault;
}

uint16_t coe_state_machine(uint16_t statewd,uint16_t cwd,uint8_t md)
{
    uint16_t ctrlwd = cwd;
    //ctrlwd = ctrlwd&0xFF70;//1-3,7置0
    switch(coe_state_turn(statewd))
    {
        case coe_not_ready:
        ctrlwd = ctrlwd&0xFF70;//1-3,7置0
        ctrlwd = ctrlwd|0x0006;//对应位置1
        break;
        case switch_disable:
        ctrlwd = ctrlwd&0xFF70;//1-3,7置0
        ctrlwd = ctrlwd|0x0006;//对应位置1
        break;
        case ready_switch:
        ctrlwd = ctrlwd&0xFF70;//1-3,7置0
        ctrlwd = ctrlwd|0x0007;//对应位置1
        break;
        case switch_on:
        ctrlwd = ctrlwd&0xFF70;//1-3,7置0
        ctrlwd = ctrlwd|0x000F;//对应位置1
        break;
        case operation_enable:
        ctrlwd = ctrlwd&0xFF70;//1-3,7置0
        ctrlwd = ctrlwd|0x000F;//对应位置1
        //if(((statewd&0x1000)^0x0000)==0) ctrlwd=0x0010;
        break;
        case quick_stop:
        ctrlwd = ctrlwd&0xFF70;//1-3,7置0
        ctrlwd = ctrlwd|0x000F;//对应位置1
        break;
        case fault_reaction:
        ctrlwd = ctrlwd&0xFF70;//1-3,7置0
        ctrlwd = ctrlwd|0x0080;//对应位置1
        break;
        case coe_fault:
        if((ctrlwd|0xFF7F) == 0xFFFF)
        {
            ctrlwd =ctrlwd&0xFF7F;//第7位为1，将其置0
            usleep(20000); //延时20ms
        }
        else
        {
            ctrlwd = ctrlwd|0x0080; //第7位为0，将其置1
        }
        break;
    }
    switch(md)
    {
        case 1:// position mode
        //判断是否生成轨迹
        //12位 not assumed，4置1，5置0，6置1（相对位置） 6置0（绝对位置）
        //ctrlwd=ctrlwd|0x0040;
        if(((statewd&0x1000)^0x0000)==0)
        {
            if(((ctrlwd&0x0010)^0x0010)==0) ctrlwd=ctrlwd&0xFFEF;
            else ctrlwd=ctrlwd|0x0010;//4置1
            ctrlwd=ctrlwd|0x0020;//change set immediately, 目标值可以实时变动，去掉之后则会运行到上一个点之后才会再运行到下一个点
        }
        //12位 assumed ，4置1，5置1，6置1（相对位置）,6置0（绝对位置）开始执行运动
        else if(((statewd&0x1000)^0x1000)==0)
        {
            ctrlwd=ctrlwd&0xFFCF;
        }
        break;
        case 3://velocity mode

        break;
    }
    return ctrlwd;
}


