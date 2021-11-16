#include <stm32l053xx.h>
#include <stdint.h>


extern void x_y_z_r(void);
extern void threshold_compare(void);

void sleepytime(void);


sleepytime()
{
  x_y_z_r();
  threshold_compare();
  threshold_compare();
  threshold_compare();
}
