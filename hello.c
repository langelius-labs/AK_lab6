#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/ktime.h>
#include <linux/slab.h>

struct head_list {
struct head_list *next;
ktime_t time;
};

MODULE_AUTHOR("Hutsaliuk Oleh IV-93");
MODULE_DESCRIPTION("Lab6");
MODULE_LICENSE("Dual BSD/GPL");

static struct head_list *head;

static int amount = 1;
module_param(amount, uint, 0444);
MODULE_PARM_DESC(amount, "Amount Hello worlds");

static int __init helloinit(void)
{
uint i;

struct head_list *var_1, *var_2;

head = kmalloc(sizeof(struct head_list *), GFP_KERNEL);

var_1 = head;
if (amount == 0) {
	pr_warn("0 was entered, doing nothing....");
} else if (amount >= 5 && amount <= 10) {
	pr_warn("Entered parameter is between 5 and 10");
} BUG_ON(amount > 10);

for (i = 0; i < amount; i++) {
	var_1->next = kmalloc(sizeof(struct head_list), GFP_KERNEL);
    if (i == 1) var_1 = NULL;
	var_1->time = ktime_get();
	pr_info("Hello World!");
	var_2 = var_1;
	var_1 = var_1->next;
}

if (amount != 0) {
	kfree(var_2->next);
	var_2->next = NULL;
}

pr_info("Amount: %d\n", amount);

return 0;
}

static void __exit helloexit(void)
{
struct head_list *var;

while (head != NULL && amount != 0) {
	var = head;
	pr_info("Time: %lld", var->time);
	head = var->next;
	kfree(var);
}
pr_info("");
}

module_init(helloinit);
module_exit(helloexit);
