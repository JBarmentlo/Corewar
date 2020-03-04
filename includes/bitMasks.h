
#define ONE			1
#define TWO			2
#define THREE		4
#define FOUR		8
#define FIVE		16
#define	SIX			32
#define	SEVEN		64
#define	EIGHT		128
#define	NINE		256
#define	TEN			512
#define	ELEVEN		1024
#define	TWELVE		2048
#define THIRTEEN	4096
#define FOURTEEN	8192
#define	FIFTEEN		16384
#define SIXTEEN		32768

#define LIVE		ONE
#define LOAD		TWO
#define STORE		THREE
#define	ADD			FOUR
#define	SUB			FIVE
#define	AND			SIX
#define	OR			SEVEN
#define XOR			EIGHT
#define ZJUMP		NINE
#define LDI			TEN
#define	STI			ELEVEN
#define	FORK		TWELVE
#define	LLD			THIRTEEN
#define	LLDI		FOURTEEN
#define	LFORK		FIFTEEN
#define	AFF			SIXTEEN

#define TWO_LOWEST  3

#define	MODULO_MASK	(MEM_SIZE - 1) //as long as MEM_SIZE is a power of 2


#define	ALL			(LIVE + LOAD + STORE + ADD + SUB + AND + OR + XOR + ZJUMP + LDI + STI + FORK + LLD + LLDI + LFORK + AFF)
#define TEST_PRINT	STI
#define	HEX_DUMP	0
#define	MAX_TURNS	20
