/******************************************************************************

	m68000.c

	M68000 CPUインタフェース関数

******************************************************************************/

#ifndef M68000_H
#define M68000_H

typedef uint32_t FASTCALL M68K_READ(const uint32_t adr);
typedef void     FASTCALL M68K_WRITE(const uint32_t adr, uint32_t data);

typedef struct M68K_struct {
	void (*Init)(void);
	void (*Close)(void);
	void (*Reset)(void);

	void (*SetFetch)(uint32_t low_adr, uint32_t high_adr, uintptr_t fetch_adr);
	void (*SetReadB)(M68K_READ *Func);
	void (*SetReadW)(M68K_READ *Func);
	void (*SetWriteB)(M68K_WRITE *Func);
	void (*SetWriteW)(M68K_WRITE *Func);

	int32_t (*Exec)(int32_t cycle);
	void (*SetIRQ)(int32_t line);

	uint32_t (*GetDReg)(uint32_t num);
	uint32_t (*GetAReg)(uint32_t num);
	uint32_t (*GetPC)(void);
	uint32_t (*GetSR)(void);
	uint32_t (*GetUSP)(void);
	uint32_t (*GetMSP)(void);

	void (*SetDReg)(uint32_t num, uint32_t val);
	void (*SetAReg)(uint32_t num, uint32_t val);
	void (*SetPC)(uint32_t val);
	void (*SetSR)(uint32_t val);
	void (*SetUSP)(uint32_t val);
	void (*SetMSP)(uint32_t val);

	int (*StateContext)(void *, int writing);
} M68K_struct;

extern M68K_struct *M68K;

extern	int32_t	ICount;

void m68000_init(void);
void m68000_reset(void);
void m68000_exit(void);
void m68000_set_irq_line(uint32_t irqline);
int32_t m68000_execute(int32_t cycles);
int32_t my_irqh_callback(int32_t level);

#endif /* M68000_H */
