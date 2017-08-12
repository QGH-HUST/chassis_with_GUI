#include <QApplication>
#include "chassis_display.h"
using   namespace   std;


int main(int argc,char *argv[])
{
    /*
    system("/home/qgh/chassis_control_test/chassis_test_001/estun-config.sh");

    int res;
    pthread_t a_thread,b_thread;
    void *thread_result;
    res = pthread_create(&a_thread, NULL, EtherCAT_comm, NULL);
    pthread_create(&b_thread, NULL, realtask, NULL);
    //pthread_join(a_thread,&thread_result);
    */
    QApplication app(argc,argv);
    chassis_display *dialog = new chassis_display;
    dialog->show();
    app.exec();

    //pthread_exit (NULL);

    return 0;
}


