#ifndef IO_H
# define IO_H

#define	IOTYPE	0xF		/* type: bits 0:3 */
#define	IOREAD	0x1		/* < */
#define	IOWRITE	0x2		/* > */
#define	IORDWR	0x3		/* <>: todo */
#define	IOHERE	0x4		/* << (here file) */
#define	IOCAT	0x5		/* >> */
#define	IODUP	0x6		/* <&/>& */

//#define	IOEVAL	BIT(4)		/* expand in << */
//#define	IOSKIP	BIT(5)		/* <<-, skip ^\t* */
//#define	IOCLOB	BIT(6)		/* >|, override -o noclobber */
//#define IORDUP	BIT(7)		/* x<&y (as opposed to x>&y) */
//#define IONAMEXP BIT(8)		/* name has been expanded */

#endif
