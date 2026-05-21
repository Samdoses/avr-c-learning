// DDS Tuning Word Macro: (Frequency * 65536) / SampleRate
#define DDS(freq) ((uint16_t)(((freq) * 65536UL) / 31250UL))

// Octave 3 Frequencies in Hz
#define C3  130.81
#define Cx3 138.59
#define D3  146.83
#define Dx3 155.56
#define E3  164.81
#define F3  174.61
#define Fx3 185.00
#define G3  196.00
#define Gx3 207.65
#define A3  220.00
#define Ax3 233.08
#define B3  246.94

// Octave 4 (Middle Octave) Frequencies in Hz
#define C4  261.63
#define Cx4 277.18
#define D4  293.66
#define Dx4 311.13
#define E4  329.63
#define F4  349.23
#define Fx4 369.99
#define G4  392.00
#define Gx4 415.30
#define A4  440.00
#define Ax4 466.16
#define B4  493.88

// Octave 5 Frequencies in Hz
#define C5  523.25
#define Cx5 554.37
#define D5  587.33
#define Dx5 622.25
#define E5  659.25
#define F5  698.46
#define Fx5 739.99
#define G5  783.99
#define Gx5 830.61
#define A5  880.00
#define Ax5 932.33
#define B5  987.77

// Octave 6 Frequencies in Hz
#define C6  1046.50
#define Cx6 1108.73
#define D6  1174.66
#define Dx6 1244.51
#define E6  1318.51
#define F6  1396.91
#define Fx6 1479.98
#define G6  1567.98
#define Gx6 1661.22
#define A6  1760.00
#define Ax6 1864.66
#define B6  1975.53
