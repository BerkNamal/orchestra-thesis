#include "net/rpl/rpl-private.h"
#define DEBUG DEBUG_NONE
#include "net/ip/uip-debug.h"
#define DEFAULT_RANK_INCREMENT  RPL_MIN_HOPRANKINC
#define MIN_DIFFERENCE (RPL_MIN_HOPRANKINC + RPL_MIN_HOPRANKINC / 2)
#include "contiki.h"
#include "net/ipv6/uip-ds6-nbr.h"
#include <stdio.h>

PROCESS(parent_child_process, "Parent child process");
AUTOSTART_PROCESSES(&parent_child_process);
PROCESS_THREAD(parent_child_process ,ev ,data){
PROCESS_BEGIN();
rpl_parent_t *p1 ; rpl_parent_t *p2 ;

rpl_rank_t r1,r2;
rpl_dag_t *dag;
uip_ds6_nbr_t *nbr1 , *nbr2;



nbr1 = rpl_get_nbr(p1);
nbr2 = rpl_get_nbr(p2);
PRINTF("GETTING THE IP OF P1 : ")
PRINT6ADDR(rpl_get_parent_ipaddr(p1));
PRINTF("GETTING THE IP OF P2 : ")
PRINT6ADDR(rpl_get_parent_ipaddr(p2));

// rank calculation to compare and select accordingly
//link metric is ETX in this case
// parent is also selected according to the rank the less the rank is , the preferable the parent is



r1 = DAG_RANK(p1 -> rank , p1 -> dag -> instance) * RPL_MIN_HOPRANKINC + nbr1 -> link_metric;

r2= DAG_RANK(p1 -> rank , p1 -> dag -> instance) * RPL_MIN_HOPRANKINC + nbr2 -> link_metric;

dag = (rpl_dag_t *)p1 ->dag;

if(r1 < r2 + MIN_DIFFERENCE  &&  r1 > r2 - MIN_DIFFERENCE){

return dag -> preferred_parent;
}
else if (r1<r2){
return (rpl_parent_t *)p1;}
else{
return (rpl_parent_t *)p2;}                      

PROCESS_END();
}


