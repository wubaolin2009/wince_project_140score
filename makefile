test:os_core.o os_cpu_a.o os_cpu_c.o os_mbox.o os_mem.o os_q.o os_sem.o os_task.o os_time.o irq.o start.o main.o lcd.o touch.o tasks.o string.o bitmap.o
# 把test.o文件链接并根据test.lds文件定址，生成test_tmp.o
	arm-elf-ld  -T 1.lds -g start.o main.o irq.o os_core.o os_cpu_a.o os_cpu_c.o os_mbox.o os_mem.o os_q.o os_sem.o os_task.o os_time.o lcd.o touch.o string.o bitmap.o tasks.o -o test_tmp.o
	arm-elf-objcopy -O binary -S test_tmp.o 1.bin
os_core.o:os_core.c
	arm-elf-gcc -g -c -o os_core.o os_core.c
os_cpu_a.o:os_cpu_a.S 
	arm-elf-gcc -g -c -o os_cpu_a.o os_cpu_a.S  
os_cpu_c.o:os_cpu_c.c 
	arm-elf-gcc -g -c -o os_cpu_c.o os_cpu_c.c 
os_mbox.o:os_mbox.c  
	arm-elf-gcc -g -c -o os_mbox.o  os_mbox.c  
os_mem.o:os_mem.c   
	arm-elf-gcc -g -c -o os_mem.o  os_mem.c  
os_q.o:os_q.c     
	arm-elf-gcc -g -c -o os_q.o  os_q.c    
os_sem.o:os_sem.c   
	arm-elf-gcc -g -c -o os_sem.o  os_sem.c  
os_task.o:os_task.c  
	arm-elf-gcc -g -c -o os_task.o os_task.c   
os_time.o:os_time.c  
	arm-elf-gcc -g -c -o os_time.o os_time.c 
irq.o:irq.c      
	arm-elf-gcc -g -c -o irq.o irq.c   
start.o:start.S
	arm-elf-gcc -g -c -o start.o start.S   
main.o:main.c   
	arm-elf-gcc -g -c -o main.o main.c   
lcd.o:lcd.c lcd.h
	arm-elf-gcc -g -c -o lcd.o lcd.c
touch.o:touch.c touch.h
	arm-elf-gcc -g -c -o touch.o touch.c
string.o:string.h string.c
	arm-elf-gcc -g -c -o string.o string.c
bitmap.o:bitmap.c bitmap.h 
	arm-elf-gcc -g -c -o bitmap.o bitmap.c
tasks.o:tasks.c
	arm-elf-gcc -g -c -o tasks.o tasks.c
	

clean:
	del os_core.o
	del os_cpu_a.o 
	del os_cpu_c.o 
	del os_mbox.o 
	del os_mem.o 
	del os_q.o 
	del os_sem.o 
	del os_task.o
	del os_time.o 
	del irq.o
	del start.o
	del main.o
	del lcd.o
	del touch.o
	del string.o
	del bitmap.o
	del tasks.o
	


