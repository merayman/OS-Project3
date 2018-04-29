
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/sched.h>
#include <linux/proc_fs.h>
#include <linux/mm.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Omer Faruk Karakaya-Musab Erayman");
/* 
 * module_param(foo, int, 0000)
 * The first param is the parameters name
 * The second param is it's data type
 * The final argument is the permissions bits, 
 * for exposing parameters in sysfs (if non−zero) at a later stage.
 */

#define next_task(p) \
	list_entry_rcu((p)->tasks.next, struct task_struct, tasks)

#define for_each_process(p) \
	for (p = &init_task ; (p = next_task(p)) != &init_task ; )
pid_t pid;
module_param(pid, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(int, "Some porcess ID");
static void print_mem(struct task_struct *task)
{
        struct mm_struct *mm;
        //struct vm_area_struct *vma_stack;
        int count = 0;
        mm = task->mm;
        struct vm_area_struct *vma_stack = mm->mmap;
        struct vm_area_struct *vma_heap = mm->mmap;
        while(vma_stack->vm_next){
        	vma_stack= vma_stack->vm_next;
            if(count <4)
                vma_heap = vma_heap->vm_next;
            count++;
        }

        /*printk(KERN_INFO "\nThis mm_struct has %d vmas.\n", mm->map_count);
        for (vma = mm->mmap ; vma ; vma = vma->vm_next) {
                printk(KERN_INFO "\nVma number %d: \n", ++count);
                printk( KERN_INFO " Starts at 0x%lx, Ends at 0x%lx\n",
                          vma->vm_start, vma->vm_end);
        }*/

        printk(KERN_INFO 
        		 "Virtual memory Starts= 0x%lx, end= 0x%lx size=%lu \n"
        		 "Code  Segment start = 0x%lx, end = 0x%lx, size=%lu \n"
                 "Data  Segment start = 0x%lx, end = 0x%lx, size=%lu \n"
                 "Argument  Segment start = 0x%lx, end = 0x%lx, size=%lu \n"
                 "Env  Segment start = 0x%lx, end = 0x%lx, size=%lu \n"
                 "Stack Segment start = 0x%lx, end = 0x%lx, size=%lu \n"
                 "Heap Segment start = 0x%lx, end = 0x%lx, size=%lu \n"
                 "number of frames used= %lu \n"
                 "total vm pages used= %lu",
                 mm->start_code, vma_stack->vm_end, vma_stack->vm_end - mm->start_code,/*vm info*/
                 mm->start_code, mm->end_code, mm->end_code - mm->start_code,/*code info*/
                 mm->start_data, mm->end_data, mm->end_data - mm->start_data,/*data info*/
                 mm->arg_start, mm->arg_end, mm->arg_end - mm->arg_start,/*argument info*/
                 mm->env_start, mm->env_end, mm->env_end - mm->env_start,/*environment info*/
                 vma_stack->vm_end, vma_stack->vm_start, vma_stack->vm_end - vma_stack->vm_start,/*stack info*/
                 vma_heap->vm_end, vma_heap->vm_start, vma_heap->vm_end - vma_heap->vm_start,/*heap info*/
                 mm->hiwater_rss,/*rss info*/
                 mm -> total_vm/*total vm info*/);
                 
         printk(KERN_INFO"hs%lx he%lx ts%lu",mm->start_brk, mm->brk, mm->brk - mm->start_brk);
         //page tabel info//
         printk(KERN_INFO""
				
			);
                 
}
static int __init hello_init(void)
{
        struct task_struct *task;
		struct task_struct *p;
		//struct task_struct *task_ptr = mytask;
		for_each_process(p)
		{
		   if(p->pid == pid)
		   	task = p;
		}
	printk(KERN_INFO "name = %s", task->comm); 
        print_mem(task);
        return 0;
}
static void __exit hello_exit(void)
{
        printk(KERN_INFO "Goodbye, world \n\n");
}
module_init(hello_init);
module_exit(hello_exit);
