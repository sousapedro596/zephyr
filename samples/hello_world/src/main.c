#include <stdio.h>
#include <zephyr/kernel.h>

void handler_sim_isr(struct k_timer *timer);

K_TIMER_DEFINE(sim_isr, handler_sim_isr, NULL);
K_TIMER_DEFINE(timer_to_be_interrupted, NULL, NULL);

k_timeout_t timeout_main = K_MSEC(100);

/* ISR timer handler to simulate HW interrupt */
void handler_sim_isr(struct k_timer *timer)
{
	/* reconfigure the timer under test, eventually we will interrupt 
	  while k_timer_start already started on main  to trigger the assert
	*/
	k_timer_start(&timer_to_be_interrupted, K_MSEC(1000), K_MSEC(1000));

	printk("simulating an interrupt\n");

}


int main()
{
	/* timer to simulate an interrupt */
	k_timer_start(&sim_isr, K_USEC(1000), K_USEC(1000));

	while(1) {
		k_timer_start(&timer_to_be_interrupted, K_MSEC(100), K_MSEC(100));
	}

}
