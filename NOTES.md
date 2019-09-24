## Task Switching
1. Stores the state of the current task in the current TSS.
2. Loads the task register with the segment selector for the new task.
3. Accesses the new TSS through a segment descriptor in the GDT.
4. Loads the state of the new task from the new TSS into the general-purpose registers, the segment registers,
the LDTR, control register CR3 (base address of the paging-structure hierarchy), the EFLAGS register, and the
EIP register.
5. Begins execution of the new task.