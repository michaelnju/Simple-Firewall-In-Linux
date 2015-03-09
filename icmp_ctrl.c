#ifndef __KERNEL__
#define __KERNEL__
#endif

#ifndef MODULE
#define MODULE
#endif
#include <linux/module.h>	 
#include <linux/sched.h>  
#include <linux/kernel.h>	 
#include <linux/netdevice.h> 
#include <linux/ip.h> 
#include <linux/tcp.h> 
#include <linux/skbuff.h> 
#include <linux/proc_fs.h> 
#include <linux/if.h> 
#include <linux/in.h> 

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#define PERMIT_PORT 80
static unsigned int test_firewall(unsigned int hooknum ,struct sk_buff **skb,
				 const struct net_device *in ,
				 const struct net_device *out,
				 int(*okfn)(struct sk_buff*))
{
	//struct tcphdr *tcph;		
	struct iphdr *iph;		 
//	struct sk_buff *skb=*pskb; 
  
	if((*skb)->protocol==htons(ETH_P_IP)) 
	{ 
		iph=(*skb)->nh.iph; 
		if (iph->protocol==IPPROTO_ICMP) 
		{ 
			printk("\nDROP a ICMP Packet"); 
			return NF_DROP; 
		} 
		if(iph->protocol==IPPROTO_TCP){ 
			 
			printk("\nPermit a valid access"); 
			return NF_ACCEPT; 
			} 
		} 
	
	return NF_ACCEPT;


}

static struct nf_hook_ops ipl1 =
{
	{NULL,NULL},
	test_firewall,
	PF_INET,
	NF_IP_PRE_ROUTING,
	NF_IP_PRI_FILTER -1 
};
int init_module()
{
	return nf_register_hook(&ipl1);
}
void cleanup_module()
{
	printk("goodbye1");
	nf_unregister_hook(&ipl1);
}
