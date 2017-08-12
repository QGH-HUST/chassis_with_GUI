#ifndef ETHERCAT_INIT_H
#define ETHERCAT_INIT_H

#include <iostream>

using namespace std;

#include <stdio.h>
#include <unistd.h>
//#include <pthread.h>

/****************************************************************************/
//EtherCAT
#include "ecrt.h" //YOU WILL NEED THIS LIBRARY
/****************************************************************************/
// Optional features
#define PRECONFIGURE_PDOS 1 //use configuration in build
#define CONFIGURE_PDOS 0 //configure at run-time
/****************************************************************************/
extern unsigned int ec_state; //servo motor state machine parameter
extern bool ethercat_state;//whether the ethercat is working.
/****************************************************************************/
// EtherCAT
static ec_master_t *master = NULL;
static ec_master_state_t master_state = {};
static ec_domain_t *domain1 = NULL;
static ec_domain_state_t domain1_state = {};

static ec_slave_config_t *sc_estun_00 = NULL;
static ec_slave_config_state_t sc_estun_00_state = {};
//static ec_slave_config_state_t *sc_enc_00_state = {};
static ec_slave_config_t *sc_estun_01 = NULL;
static ec_slave_config_state_t sc_estun_01_state = {};

/****************************************************************************/
#define NUMSLAVES 6
// process data
static uint8_t *domain1_pd = NULL;
//HERE WE BEGIN TO DEFINE THE PDO ENTRIES AND WHERE THEY WILL APPEAR IN THE PROCESS
//DATA DOMAIN
//definitions for the bus connections and expected slave positions
#define ESTUN_00_Pos          0, 0
#define ESTUN_01_Pos          0, 1

#define ESTUN_00   0x0000060a, 0x00000001
#define ESTUN_01   0x0000060a, 0x00000001

typedef enum {
    coe_not_ready    = 0,
    switch_disable   = 1,
    ready_switch     = 2,
    switch_on        = 3,
    operation_enable = 4,
    quick_stop       = 5,
    fault_reaction   = 6,
    coe_fault        = 7
} CoEstate;

// offsets for PDO entries
static unsigned int off_estun_00_ctrlwd;         //control word   0x6040
static unsigned int off_estun_00_statwd;        //state word 0x6041
static unsigned int off_estun_00_modop;       //mode of operation 0x6060
static unsigned int off_estun_00_modds;       //mode of operation dispaly 0x6061
static unsigned int off_estun_00_tarvel;        //target velocity 0x60ff
static unsigned int off_estun_00_actvel;        //actual velocity 0x606c
static unsigned int off_estun_00_tarpos;        //target position 0x607a
static unsigned int off_estun_00_actpos;        //actual position 0x6064
static unsigned int off_estun_00_provel;        //profile velocity 0x6081
static unsigned int off_estun_00_endvel;        //end velocity 0x6082
static unsigned int off_estun_00_proacc;        //profile acceleration 0x6083
static unsigned int off_estun_00_prodec;        //profile deceleration 0x6084

static unsigned int off_estun_01_ctrlwd;         //control word   0x6040
static unsigned int off_estun_01_statwd;        //state word 0x6041
static unsigned int off_estun_01_modop;       //mode of operation 0x6060
static unsigned int off_estun_01_modds;       //mode of operation dispaly 0x6061
static unsigned int off_estun_01_tarvel;        //target velocity 0x60ff
static unsigned int off_estun_01_actvel;        //actual velocity 0x606c
static unsigned int off_estun_01_tarpos;        //target position 0x607a
static unsigned int off_estun_01_actpos;        //actual position 0x6064
static unsigned int off_estun_01_provel;        //profile velocity 0x6081
static unsigned int off_estun_01_endvel;        //end velocity 0x6082
static unsigned int off_estun_01_proacc;        //profile acceleration 0x6083
static unsigned int off_estun_01_prodec;        //profile deceleration 0x6084



//NOTE THAT THE DOMAIN REGISTRATION REQUIRES ONLY THE BASE ADDRESS OF THE I/O ON THE
//MODULES (SEE BELOW)
const static ec_pdo_entry_reg_t domain1_regs[] = {
    {ESTUN_00_Pos, ESTUN_00 , 0x6040, 0, &off_estun_00_ctrlwd},
    {ESTUN_00_Pos, ESTUN_00 , 0x6041, 0, &off_estun_00_statwd},
    {ESTUN_00_Pos, ESTUN_00 , 0x6060, 0, &off_estun_00_modop},
    {ESTUN_00_Pos, ESTUN_00 , 0x6061, 0, &off_estun_00_modds},
    {ESTUN_00_Pos, ESTUN_00 , 0x60ff, 0, &off_estun_00_tarvel},
    {ESTUN_00_Pos, ESTUN_00 , 0x606c, 0, &off_estun_00_actvel},
    {ESTUN_00_Pos, ESTUN_00 , 0x607a, 0, &off_estun_00_tarpos},
    {ESTUN_00_Pos, ESTUN_00 , 0x6064, 0, &off_estun_00_actpos},
    {ESTUN_00_Pos, ESTUN_00 , 0x6081, 0, &off_estun_00_provel},
    {ESTUN_00_Pos, ESTUN_00 , 0x6082, 0, &off_estun_00_endvel},
    {ESTUN_00_Pos, ESTUN_00 , 0x6083, 0, &off_estun_00_proacc},
    {ESTUN_00_Pos, ESTUN_00 , 0x6084, 0, &off_estun_00_prodec},

    {ESTUN_01_Pos, ESTUN_01 , 0x6040, 0, &off_estun_01_ctrlwd},
    {ESTUN_01_Pos, ESTUN_01 , 0x6041, 0, &off_estun_01_statwd},
    {ESTUN_01_Pos, ESTUN_01 , 0x6060, 0, &off_estun_01_modop},
    {ESTUN_01_Pos, ESTUN_01 , 0x6061, 0, &off_estun_01_modds},
    {ESTUN_01_Pos, ESTUN_01 , 0x60ff, 0, &off_estun_01_tarvel},
    {ESTUN_01_Pos, ESTUN_01 , 0x606c, 0, &off_estun_01_actvel},
    {ESTUN_01_Pos, ESTUN_01 , 0x607a, 0, &off_estun_01_tarpos},
    {ESTUN_01_Pos, ESTUN_01 , 0x6064, 0, &off_estun_01_actpos},
    {ESTUN_01_Pos, ESTUN_01 , 0x6081, 0, &off_estun_01_provel},
    {ESTUN_01_Pos, ESTUN_01 , 0x6082, 0, &off_estun_01_endvel},
    {ESTUN_01_Pos, ESTUN_01 , 0x6083, 0, &off_estun_01_proacc},
    {ESTUN_01_Pos, ESTUN_01 , 0x6084, 0, &off_estun_01_prodec},

    {}
};

static char slaves_up = 0;

void chassis_upload_ethercat();
void chassis_download_ethercat();
void check_domain1_state(void);
void check_master_state(void);
void check_slave_config_states();
int EtherCAT_comm_int(void);
void *EtherCAT_comm(void *arg);
CoEstate coe_state_turn(uint16_t statewd);
uint16_t coe_state_machine(uint16_t statewd,uint16_t cwd,uint8_t md);


#endif // ETHERCAT_INIT_H
