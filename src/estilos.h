#ifndef ESTILOS_H
#define ESTILOS_H


#define RESET "\x1b[0m"   // Reset para volver a los colores por defecto

// ROBOT 
#define G "\x1b[38;2;0;255;0m"       
#define PP "\x1b[38;2;255;0;0m"
#define B "\x1b[38;2;0;102;255m"      
#define O "\x1b[38;2;255;85;0m"       
#define R "\x1b[38;2;255;0;0m"           
#define Y "\033[38;2;57;255;20m" 
#define NEON_PURPLE "\x1b[38;2;255;0;255m"  


#define CB "\x1b[38;2;30;95;235m"  
#define CB2 "\x1b[38;2;29;93;236m"  
#define DARK_NEON_YELLOW "\x1b[38;2;255;255;0m"
#define RESET_COLOR "\x1b[0m"


// pastel neon 
#define PASTEL_PINK "\x1b[38;2;255;182;193m" 
#define PY "\x1b[38;2;255;255;128m"  
#define PASTEL_ORANGE "\x1b[38;2;255;204;128m" 
#define PASTEL_GREEN "\x1b[38;2;153;255;153m" 
#define PASTEL_BLUE "\x1b[38;2;173;216;230m"   
#define PASTEL_PURPLE "\x1b[38;2;230;190;255m" 

// oscuros
#define DN "\x1b[38;2;255;153;0m" 
#define DARK_NEON_YELLOW "\x1b[38;2;255;255;0m"
#define DARK_NEON_RED "\x1b[38;2;255;51;0m"    
#define DB "\x1b[38;2;0;102;255m"   

#define N "\x1b[38;2;0;0;0m"  

//funciones de bienvenida y carga que solo muestran el logo y los diseños (void)
void mostrarBienvenida();
void simulacionCargaBienvenida();

#endif
