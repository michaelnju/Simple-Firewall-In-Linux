#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <linux/tcp.h>

struct nf_hook_ops nfkiller;
unsigned char *deny_port1 = "\x00\x15";
unsigned char *deny_port2 = "\x00\x14";

//define the funciton 
unsigned int lwfw_hookfn(unsigned int hooknum,
                       struct sk_buff **skb,
                       const struct net_device *in,
                       const struct net_device *out,
                       int (*okfn)(struct sk_buff *))
{
   struct sk_buff *sk = *skb;

   if (!sk ) return NF_ACCEPT;
   if (!(sk->nh.iph)) return NF_ACCEPT;

   if (sk->nh.iph->protocol == IPPROTO_TCP) {
      struct tcphdr *thead = (struct tcphdr *)(sk->data + (sk->nh.iph->ihl * 4));
      if ((thead->source) == *(unsigned short *)deny_port1||(thead->source)==*(unsigned short *)deny_port2||(thead->dest)==*(unsigned short *)deny_port1||(thead->dest)==*(unsigned short *)deny_port2)
         return NF_DROP;
   }
   return NF_ACCEPT;
}



// define the hook
int FTP_init(void)
{
        
        nfkiller.hook = lwfw_hookfn;
        nfkiller.hooknum = NF_IP_PRE_ROUTING;   
        nfkiller.pf = PF_INET;                   
        nfkiller.priority = NF_IP_PRI_FIRST;    
        nf_register_hook(&nfkiller);
        return 0;
}

// register the hook
void FTP_exit(void)
{
        nf_unregister_hook(&nfkiller);
}

module_init(FTP_init);
module_exit(FTP_exit);
