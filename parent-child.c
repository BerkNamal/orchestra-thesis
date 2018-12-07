#include "net/rpl/rpl-private.h"

#define DEBUG DEBUG_NONE
#include "net/ip/uip-debug.h"
#include "net/ipv6/uip-ds6-nbr.h"

#define DEFAULT_RANK_INCREMENT  RPL_MIN_HOPRANKINC

#define MIN_DIFFERENCE (RPL_MIN_HOPRANKINC + RPL_MIN_HOPRANKINC / 2)


static rpl_parent_t *best_parent(rpl_parent_t *p1 , rpl_parent_t *p2)

{
rpl_rank_t r1,r2;
rpl_dag_t *dag;
uip_ds6_nbr_t *nbr1 , *nbr2;

nbr1 = rpl_get_nbr(p1);
nbr2 = rpl_get_nbr(p2);
PRINT6ADDR(rpl_get_parent_ipaddr(p1));
PRINT6ADDR(rpl_get_parent_ipaddr(p2));

// rank calculation to compare and select accordingly
//link metric is ETX in this case
// parent is also selected according to the rank the less the rank is , the preferable the parent is


r1 = DAG_RANK(p1 -> rank , p1 -> dag -> instance) * RPL_MIN_HOPRANKINC + nbr1 -> link_metric;

r2= DAG_RANK(p1 -> rank , p1 -> dag -> instance) * RPL_MIN_HOPRANKINC + nbr2 -> link_ metric;

dag = (rpl_dag_t *)p1 ->dag;

if(r1 < r2 + MIN_DIFFERENCE  &&  r1 > r2 - MIN_DIFFERENCE){

return dag -> preferred_parent;
}
else if (r1<r2){
return p1;}
else{
return p2;  }                    

}


