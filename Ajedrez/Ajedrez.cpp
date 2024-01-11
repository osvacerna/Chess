#include "Shell.cpp"

const int ancho = 518;
const int alto = 512;

Window ventana("Proyecto Shell", ancho, alto);

//Pieces
#define ROOK 0
#define KNIGHT 1
#define BISHOP 2
#define QUEEN 3
#define KING 4
#define PAWN 5

#define NEGRO 0
#define BLANCO 1

typedef struct{
	int posx, posy, color, type, visible;
} piece;

//Funciones
COLORREF** buffer;
void playchess();
void initPieces(piece **pieces);
void createpieces(COLORREF ****wbpieces, int *nr, int *nc);
COLORREF **createimage(int nr, int nc);
void initbuffer(COLORREF** fondo);
void createmenu(COLORREF ****menus, int *pr, int *pc);
void cargardatos(piece **pieces,FILE *filein);
void salvardatos(piece **pieces, FILE *fileout);
void ubicaclic(int* x, int* y);
const COLORREF transparente = RGB(250, 30, 240);
void copytobuffer(COLORREF** img, int nr, int nc, int x, int y);
void freeimage(COLORREF** image);


int main(int argc, char *argv[]){
	
	playchess();
	
	Sleep(2000);
	return 0;
	
	return MainLoop();
}

void playchess(){
	
	//Para lo relacionado con el movimiento de las piezas
	int  i, k, x, y, nr, nc, pn1, pn2, m = -1;
	int encontro, continuar, pr, pc;
	int *auxx, *auxy;
	
	auxx = &x;
	auxy = &y;
	
	//Para los datos de las piezas
	piece *pieces;
	piece **aux;
	
	pieces = (piece*)malloc(32*sizeof(piece));
	
	aux = &pieces;
	
	initPieces(aux);
	
	//Para guardar las imagenes en matrices
	int *aux1, *aux2;
	COLORREF ***wbpieces;
	COLORREF ****aux3;
	
	aux1 = &nr;
	aux2 = &nc;
	aux3 = &wbpieces;
	
	createpieces(aux3, aux1, aux2);
	
	//Para dibujar el tablero de fondo
	buffer = createimage(alto, ancho);
	
	//Para las imagenes de los menus
	int *aux4, *aux5;
	COLORREF ***menus;
	COLORREF ****aux6;
	
	aux4 = &pr;
	aux5 = &pc;
	aux6 = &menus;
	
	createmenu(aux6, aux4, aux5);
	
	//Menú de inicio
	while(1){
		
		//Presentamos los botones
		initbuffer(buffer);
		
		copytobuffer(menus[0], pr, pc, 128, 64);
		copytobuffer(menus[1], pr, pc, 128, 192);
		ventana.PlotCBitmap(buffer, alto, ancho, 0, 0, 1);
		
		//Esperamos un click del usario
		int resultado = MouseHit(&x, &y);
		
		if (resultado == 1){
			
			//Si eligio jugar una nueva partida, avanzamos directamente al juego
			if( x >= 150 && x <= 357 && y >= 82 && y <= 155){
				break;
			}
			
			//Si elegio cargar la anterior partida, llamamos a la función para obtener los datos del txt
			if( x >= 150 && x <= 357 && y >= 210 && y <= 283){
				FILE *filein = fopen("Salvar.txt", "r");
				cargardatos(aux, filein);
				fclose(filein);
				break;
			}
		}
		
		Sleep(100);
	}
	
	//JUEGO AJEDREZ
	while(1){
		
		//Dibujamos el fondo y todas las piazas de acuerdo a la información que se tiene
		initbuffer(buffer);
		
		//Aquí dibujamos el marco para seleccionar una pieza
		if(m == 1){
			copytobuffer(menus[2], nr, nc, pieces[pn1].posx, pieces[pn1].posy);
		}
		
		//Aquí dibujamos todas las piezas visibles
		for(i = 0; i < 32; i++){
			
			if(pieces[i].visible == 1){
				copytobuffer(wbpieces[i], nr, nc, pieces[i].posx, pieces[i].posy);
			}
		}
		
		ventana.PlotCBitmap(buffer, alto, ancho, 0, 0, 1);
		
		//Guardamos el número de pieza del movimiento anterior(Util más tarde)
		pn2 = pn1;
		
		//Preguntamos por un click
		int player_click = MouseHit(&x, &y);
		
		//El click derecho selecciona y mueve piezas
		if (player_click == 1){
			
			//Guardamos el juego en cada movimiento
			if(m == 1){
				FILE *fileout = fopen("Salvar.txt", "w");
				salvardatos(aux, fileout);
				fclose(fileout);
			}
			//Esclamos el click para poder trabajar con la cacilla completa
			ubicaclic(auxx, auxy);
			
			//Si m (variable que te permite saber si estamos avanzando o seleccionando pieza)
			//es positiva entonces avanzamos (Inicialiazamos m a -1, el primer click es para seleccionar pieza y empezar a jugar)
			if(m == 1){
				
				//Avanzar solo representa modificar la información contenida en las estructuras pieces
				pieces[pn1].posx = x;
				pieces[pn1].posy = y;
			}
			
			encontro = 0;
			//Buscamos si dentro de la cacilla seleccionada hay una pieza
			for(i = 0; i < 32; i++){
				
				//Cuando encuentra pieza
				if((x == pieces[i].posx && y == pieces[i].posy) && pieces[i].visible){
					
					//Para identificar cuando el usario dio click en una casilla vacia
					encontro++;
					//pn1 es el número de pieza que avanzará 
					pn1 = i;
					
					//Si la pieza anterior es de un color distinto a la actual y estamos avanzando dejamos de buscar
					//(significa que las negras comeran a las blancas)
					if(pieces[pn2].color == 0 && pieces[pn1].color == 1 && m == 1){
						break;
					}
				}
			}
			
			//Si la pieza anterior y la nueva tienen la misma posicion y además tienen distinto color
			if(pieces[pn2].posx == pieces[pn1].posx && pieces[pn2].posy == pieces[pn1].posy && pieces[pn2].color != pieces[pn1].color){
				
				//La pieza actual fue comida y la sacamos del tablero			
				pieces[pn1].visible = 0;
				pieces[pn1].posx = 500;
				pieces[pn1].posy = 500;
			}
			
			//Se repite el proceso de selección por que no encontró pieza
			if(encontro == 0){
				m = m*-1;
			}
			
			//Cambiamos de movimiento a seleción y viceversa
			m = m*-1;
		}
		else{
			
			//Cuando el usario da click derecho pausa el juego y se abre el menú de pausa
			if (player_click == 2){
				while(1){
					
					//Dibujamos el fondo y los botones de este menú
					initbuffer(buffer);
		
					copytobuffer(menus[0], pr, pc, 128, 64);
					copytobuffer(menus[3], pr, pc, 128, 192);
					copytobuffer(menus[4], pr, pc, 128, 320);
					ventana.PlotCBitmap(buffer, alto, ancho, 0, 0, 1);
					
					//Preguntamos por una opción
					int resultado = MouseHit(&x, &y);
		
					if (resultado == 1){
						
						//Si el usario presiona Play, despausa el juego y continua donde se quedó
						if( x >= 150 && x <= 357 && y >= 82 && y <= 155){
							continuar = 1;
							break;
						}
						
						//Si el usario presiona Back, obtenemos la información del juego inmediata anterior del txt
						//De esta forma, logramos regresar un movimiento 
						if( x >= 150 && x <= 357 && y >= 210 && y <= 283){
							FILE *filein = fopen("Salvar.txt", "r");
							cargardatos(aux, filein);
							fclose(filein);			
							continuar = 1;
							break;
						}
						
						//Si se presiona Exit avandonamos el juego y se cierra la aplicación
						if( x >= 150 && x <= 357 && y >= 338 && y <= 411){
							continuar = -1;
							break;
						}
					}
		
					Sleep(100);
				}
				
				//Solo la opción de exit rompe el While(1) del juego
				if(continuar == -1){
					break;
				}
			}
		}
		
		Sleep(100);
	}
	
	//La despedida
	initbuffer(buffer);
	copytobuffer(menus[5], pr, pc, 128, 192);
	ventana.PlotCBitmap(buffer, alto, ancho, 0, 0, 1);
	
	//Se libera toda la memoria
	free(pieces);
	freeimage(buffer);
	for(i = 0; i < 32; i++){
		freeimage(wbpieces[i]);
	}
	free(wbpieces);
	for(i = 0; i < 32; i++){
		freeimage(menus[i]);
	}
	free(menus);
}

void cargardatos(piece **pieces, FILE *filein){
	int i;
	
	//Obtenemos la informacion del juego desde un txt
	for(i = 0; i < 16; i++){
		fscanf(filein, "%d", &pieces[0][i].color);
		fscanf(filein, "%d", &pieces[0][i].posx);
		fscanf(filein, "%d", &pieces[0][i].posy);
		fscanf(filein, "%d", &pieces[0][i].visible);
		fscanf(filein, "%d", &pieces[0][i+16].color);
		fscanf(filein, "%d", &pieces[0][i+16].posx);
		fscanf(filein, "%d", &pieces[0][i+16].posy);
		fscanf(filein, "%d", &pieces[0][i+16].visible);
	}
}

void salvardatos(piece **pieces, FILE *fileout){
	
	int i;
	
	//Guardamos en un txt la información del juego
	for(i = 0; i < 16; i++){
		fprintf(fileout, "%d ", pieces[0][i].color);
		fprintf(fileout, "%d ", pieces[0][i].posx);
		fprintf(fileout, "%d ", pieces[0][i].posy);
		fprintf(fileout, "%d\n", pieces[0][i].visible);
		fprintf(fileout, "%d ", pieces[0][i+16].color);
		fprintf(fileout, "%d ", pieces[0][i+16].posx);
		fprintf(fileout, "%d ", pieces[0][i+16].posy);
		fprintf(fileout, "%d\n", pieces[0][i+16].visible);
	}
}

void createmenu(COLORREF ****menus, int *pr, int *pc){
	
	int i;
	
	char *name[] = {"play.bmp", "carga.bmp", "marco.bmp" , "back.bmp", "exit.bmp", "bye.bmp"};
	
	//Obtenemos el tamaño de las imagenes (todos tienen el mismo)
	DimensionesBmp(name[0], &pr[0], &pc[0]);
	
	//Reservamos memoria para todas las imagenes
	menus[0] = (COLORREF***)malloc(6*sizeof(COLORREF**));
	
	//Reservamos memoria para las 6 botones de los menus
	for(i = 0; i < 6; i++){
		menus[0][i] = createimage(pr[0], pc[0]);
	}
	
	//Llenamos todas las matrices con las imagenes
	for(i = 0; i<6; i++){	
		LeeBmpColor( menus[0][i], name[i]);
	}
}

void initbuffer(COLORREF** fondo){
	
	//Leemos la imagen tablero de fondo
	LeeBmpColor(buffer, "tablero.bmp");
	
}

void ubicaclic(int* x, int* y){
	
	int i;
	
	//Escalamos todos los clicks a posiciones multiplos de 64
	for(i = 0; i < 8; i++){
		
		if(*x < 64*(i+1) && *x > 64*i){
			
			*x = 64*i;
		}
		if(*y < 64*(i+1) && *y > 64*i){
				
			*y = 64*i;
		}
	}
}

void createpieces(COLORREF ****wbpieces, int *nr, int *nc){
	
	int i;
	
	char *namepiece[] = {"w_rook.bmp", "w_knight.bmp", "w_bishop.bmp", "w_queen.bmp", "w_king.bmp", "w_bishop.bmp", "w_knight.bmp", "w_rook.bmp", "w_pawn.bmp",
						 "b_rook.bmp", "b_knight.bmp", "b_bishop.bmp", "b_queen.bmp", "b_king.bmp", "b_bishop.bmp", "b_knight.bmp", "b_rook.bmp", "b_pawn.bmp"};
	
	//Obtenemos el tamaño de las imagenes (todos tienen el mismo)
	DimensionesBmp(namepiece[0], &nr[0], &nc[0]);
	
	//Reservamos memoria para todas las imagenes
	wbpieces[0] = (COLORREF***)malloc(32*sizeof(COLORREF**));
	
	//Reservamos memoria para las 32 piezas
	for(i = 0; i < 32; i++){
		wbpieces[0][i] = createimage(nr[0], nc[0]);
	}
	
	//Llenamos todas las matrices con las imagenes
	for(i = 0; i<8; i++){
		
		LeeBmpColor( wbpieces[0][i], namepiece[i]);
		LeeBmpColor( wbpieces[0][i+16], namepiece[i+9]);
	}
	
	for(i = 8; i < 16; i++){
		
		LeeBmpColor(wbpieces[0][i], namepiece[8]);
		LeeBmpColor(wbpieces[0][i+16], namepiece[17]);
	}
}

void initPieces(piece **pieces){
	
	int i;
	
	//Tipo de ficha
	for(i = 0; i<5; i++){
		
		pieces[0][i].type = i;
		pieces[0][i+16].type = i;
	}
	
	pieces[0][5].type = BISHOP;
	pieces[0][21].type = BISHOP;

	pieces[0][6].type = KNIGHT;
	pieces[0][22].type = KNIGHT;
	
	pieces[0][7].type = ROOK;
	pieces[0][23].type = ROOK;
	
	for(i = 8; i < 16; i++){
		
		pieces[0][i].type = PAWN;
		pieces[0][i+16].type = PAWN;
	}
	
	//Color y visibilidad
	for(i = 0; i<16; i++){
		
		pieces[0][i].color = BLANCO;
		pieces[0][i+16].color = NEGRO;
		
		pieces[0][i].visible = 1;
		pieces[0][i+16].visible = 1;
	}
	
	//Posición
	for(i = 0; i < 8; i++){
		
		pieces[0][i].posx = 64*i;
		pieces[0][i].posy = 448;
		
		pieces[0][i+16].posx = 64*i;
		pieces[0][i+16].posy = 0;
	}
	
	for(i = 8; i < 16; i++){
		
		pieces[0][i].posx = 64*(i-8);
		pieces[0][i].posy = 384;
		
		pieces[0][i+16].posx = 64*(i-8);
		pieces[0][i+16].posy = 64;
	}
}

void copytobuffer(COLORREF** img, int nr, int nc, int x, int y){
	
	int i, j;
	
	for(i = y; i < y+nr; i++){
		for(j = x; j < x+nc; j++){
			
			if(i < alto && j < ancho){
				
				//Eliminamos el color rosa de las imagenes 
				unsigned char R = GetRValue(img[i-y][j-x]);
				unsigned char G = GetGValue(img[i-y][j-x]);
				unsigned char B = GetBValue(img[i-y][j-x]);
			
				if( (R != GetRValue(transparente)) && (G != GetGValue(transparente)) && (B != GetBValue(transparente)) ){
					
					//Guardamos todos los demas colores
					buffer[i][j] = img[i-y][j-x];
				}
			}
		}
	}
}

COLORREF **createimage(int nr, int nc){
	
	COLORREF **image;
	COLORREF *dat;
	int i, j;
	
	//Se pide memoria para el doble apuntador y se regresa 1 cuando es posible y -1 cuando no
	image = (COLORREF**)malloc(nr * sizeof(COLORREF*));
	if(image == NULL){
		return image;
	}
	
	//Se pide memoria para la matriz entera y continua en memoria
	dat = (COLORREF*)malloc(nr * nc * sizeof(COLORREF));
	
	//Se apunta cada inicio de renglon a su parte correspondiente de la matriz
	for(i = 0, j = 0; j < nr ; i = i + nc, j++){
		
		image[j] = &dat[i];
	}
	
	return image;
}

void freeimage(COLORREF** image){
	
	//Se libera la memoria del doble apuntador
	free(image[0]);
	//Se libera la memoria de la matriz entera y en una sola linea
	free(image);
}
