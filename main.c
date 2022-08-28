#include <stdio.h>
#include <stdlib.h>

#define blen 100
#define maxradek 100
#define vzlen 4
#define pomlen 100

struct fronta{
	char buffer[blen];
	char pom_buf[pomlen];
	int b_zac, b_kon, pom_zac, pom_kon;
	
};

void init_fronta(struct fronta *pt);
void put_mainfronta(struct fronta *pt, char item);
void get_mainfronta(struct fronta *pt, char *item);


void pombufTofronta(struct fronta *pt);


char nactiznak(struct fronta *pt, FILE *fp);
int jeFrontaprazdna(struct fronta *pt);


//int nacti_radek(char *radek, int lim, struct fronta *pt);


void put_pombuf(struct fronta *pt, char znak);
void get_pombuf(struct fronta *pt, char *item);


void clear_mainfronta(struct fronta *pt);
void clear_pombuf(struct fronta *pt);



int main(int argc, char **argv)
{
	
	
	FILE *file = fopen("auto.txt", "r");
	
	//char radek[maxradek];
	char *vzorek = "auto";
	
	struct fronta Fronta;
	
	init_fronta(&Fronta);

	int z, j = 0; 
	if((z = nactiznak(&Fronta, file)) != EOF) put_pombuf(&Fronta, z);
	
	while( z != EOF && j < vzlen ){
		
		if(z != vzorek[j] && z != '\n'){
			j = 0;
			clear_mainfronta(&Fronta);
			pombufTofronta(&Fronta);
			get_mainfronta(&Fronta, &z);
			clear_pombuf(&Fronta);
			
			while(!jeFrontaprazdna(&Fronta)){
				z = nactiznak(&Fronta, file);
				put_pombuf(&Fronta, z);
				if(z != vzorek[j++]){
					j = 0;
					get_pombuf(&Fronta, &z);
				}
			}
			
		}else if(z != '\n') j++;
				
				
		z = nactiznak(&Fronta, file);
		put_pombuf(&Fronta, z);
	}
	
	if(j >= vzlen) puts("je tam");
	else puts("neni");                   //ctrl + z  EOF
	
	

	
	return 0;
}

/*int nacti_radek(char *radek, int lim, struct fronta *pt){
	int z, i;
	
	for(i = 0; i < lim - 1 && (z = nactiznak(pt)) != EOF && z != '\n'; i++)
		radek[i] = z;
	
	if( z == '\n')
		radek[i++] = z;
	
	radek[i] = '\0';
	return i;
}*/


char nactiznak(struct fronta *pt, FILE *fp){
	
	char ch;
	if(!jeFrontaprazdna(pt)){
		
		get_mainfronta(pt, &ch);
		
		return ch;
		
	}else return getc(fp); 	
}

int jeFrontaprazdna(struct fronta *pt){
	return (pt->b_zac + 1 == pt->b_kon);
}

int jePombufprazdny(struct fronta *pt){
	return (pt->pom_zac + 1 == pt->pom_kon);
}

void pombufTofronta(struct fronta *pt){
	
	char z;
	while(!jePombufprazdny(pt)){
		get_pombuf(pt, &z);
		put_mainfronta(pt, z);
	}
}

void init_fronta(struct fronta* pt){
	pt->b_kon = 0;
	pt->b_zac = -1;
	
	pt->pom_zac = -1;
	pt->pom_kon = 0;
	
	
	memset(pt->buffer, 0, blen);
	memset(pt->pom_buf, 0, pomlen);
}

void clear_mainfronta(struct fronta *pt){
	pt->b_kon = 0;
	pt->b_zac = -1;
	memset(pt->buffer, 0, blen);
}


void clear_pombuf(struct fronta *pt){
	pt->pom_kon = 0;
	pt->pom_zac = -1;
	memset(pt->pom_buf, 0, pomlen);
}


void put_mainfronta(struct fronta *pt, char item){
	
	if((pt->b_kon) % blen == pt->b_zac || pt->b_kon >= blen){
		puts("fronta je plno");
		return;
	}else{
		//printf("vkladam do buf: %c\n", item);
		pt->b_kon = pt->b_kon % blen;
        pt->buffer[pt->b_kon] = item;
        pt->b_kon++;
	} 
}

void put_pombuf(struct fronta *pt, char item){
	
	if((pt->pom_kon) % pomlen == pt->pom_zac || pt->pom_kon >= pomlen){
		puts("pom je plno");
		return;
	}else{
		//puts("vkladam do pom");
		//printf("vkladam do pom: %c\n", item);
		pt->pom_kon = pt->pom_kon % pomlen;
        pt->pom_buf[pt->pom_kon] = item;
        pt->pom_kon++;
	} 
}

void get_mainfronta(struct fronta *pt, char *item){
	
	if(pt->b_zac + 1 == pt->b_kon){
		printf("fronta je prazdna");
		return;
	}
	*item = pt->buffer[++pt->b_zac];
}

void get_pombuf(struct fronta *pt, char *item){
	
	if(pt->pom_zac + 1 == pt->pom_kon){
		printf("pom je prazdna");
		return;
	}
	*item = pt->pom_buf[++pt->pom_zac];
}


