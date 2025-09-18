/*
 *	testes para o tp2 de prog1 
 *	ultima alteracao em 15/09/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include "racional.h"
#define MAX 100
/* estrutura que representa um número racional */
struct racional {
  long num;          /* numerador   */
  long den;          /* denominador */
};


long aleat (long min, long max)
{
	return min + rand() % (max - min + 1);
}


/* Máximo Divisor Comum entre a e b      */
/* calcula o MDC pelo método de Euclides */
long mdc (long a, long b)
{
	long resto, aux;
	
	if (b > a)
	{
		aux = a;
		a = b;
		b = aux;
	}
		
	while (b != 0)
	{
		resto = a % b;
		a = b;
		b = resto;
	}
	
	return a;
}


/* Mínimo Múltiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc (long a, long b)
{
	return ( (a * b) / mdc(a, b) );
}


/* Recebe um número racional e o simplifica.
 * Por exemplo, ao receber 10/8 deve retornar 5/4.
 * Se ambos numerador e denominador forem negativos, deve retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Se r for inválido, devolve-o sem simplificar. */
struct racional simplifica_r (struct racional r)
{
	long aux = mdc(r.num, r.den);
	
	if (! valido_r(r))
		return r;
		
	if (mdc(r.num, r.den) != 1)
	{
		r.num =  r.num / aux;
		r.den = r.den / aux;
	}
	
	if (r.den < 0) 
	{
		r.num = (- r.num);
		r.den = (- r.den);
	}
	
	return r;
}


/* funcoes do racional.h */

long numerador_r (struct racional r)
{
	return r.num;
}


long denominador_r (struct racional r)
{
	return r.den;
}


struct racional cria_r (long numerador, long denominador)
{
	struct racional r;
	
	scanf("%ld", &r.num);
	scanf("%ld", &r.den);
	return r;
}


int valido_r (struct racional r) 
{
	if (r.den == 0)
		return 0;
	else
		return 1;
}


struct racional sorteia_r (long min, long max)
{
	struct racional r;
	
	r.num = aleat(min, max); 
	r.den = aleat(min, max); 
	
	return simplifica_r(r);
}


void imprime_r (struct racional r)
{
	r = simplifica_r(r);
	
	if (! valido_r(r))
	{
		printf("NaN");
		return;
	}
	
	if (r.num == 0)
	{
		printf("0");
		return;
	}
	
	if (r.den == 1)
	{
		printf("%ld", r.num);
		return;
	}
	
	if (r.num == r.den)
	{
		printf("1");
		return;
	}
	printf("%ld/%ld", r.num, r.den);
	
	return;
}


int compara_r (struct racional r1, struct racional r2)
{
	if ( (! valido_r(r1)) || (! valido_r(r2)) )
		return -2;
		
	//para comparar coloco os dois na mesma base
	r1.num = (r1.num * r2.den) / mdc(r1.den, r2.den);
	r2.num = (r2.num * r1.den) / mdc(r1.den, r2.den);
	r1.den = mmc(r1.den, r2.den);
	r2.den = mmc(r1.den, r2.den);
	
	if (r1.num < r2.num )
		return -1;
	if (r1.num > r2.num)
		return 1;
		
	//retorna 0 se forem iguais	
	return 0;	
}


int soma_r (struct racional r1, struct racional r2, struct racional *r3)
{
	if ( ((! valido_r(r1)) || (! valido_r(r2))) || (r3 == NULL))
		return 0;
		
	r3 -> num = ((r1.num * r2.den) + (r1.den * r2.num)) / mdc(r1.den, r2.den);   
	r3 -> den = mmc(r1.den, r2.den);
	*r3 = simplifica_r(*r3);
	
	return 1;
}	


int subtrai_r (struct racional r1, struct racional r2, struct racional *r3)
{
	if ( ((! valido_r(r1)) || (! valido_r(r2))) || (r3 == NULL))
		return 0;
		
	r3 -> num = ((r1.num * r2.den) - (r1.den * r2.num)) / mdc(r1.den, r2.den);   
	r3 -> den = mmc(r1.den, r2.den);
	*r3 = simplifica_r(*r3);
	 
	return 1;
}


int multiplica_r (struct racional r1, struct racional r2, struct racional *r3)
{
	if ( ((! valido_r(r1)) || (! valido_r(r2))) || (r3 == NULL))
		return 0;
	r3 -> num = r1.num * r2.num;   
	r3 -> den = r1.den * r2.den;
	*r3 = simplifica_r(*r3);
	 
	return 1;
}


int divide_r (struct racional r1, struct racional r2, struct racional *r3)
{
	long aux;
	if ( ((! valido_r(r1)) || (! valido_r(r2))) || (r3 == NULL))
		return 0;
		
	aux = r2.den;
	r2.den = r2.num;
	r2.num = aux;
	
	multiplica_r(r1, r2, r3);
	*r3 = simplifica_r(*r3);
	
	if (r3->den == 0)
		return 0;
	
	return 1;
}


//*******************************************************************************
//funcoes para o vetor

/*void inicializa_vetor(struct racional *v)
{
	int i;	
	for (i=0; i <= MAX; i++)
		v[i].num = 0;
}


void imprime_feio (struct racional *v)
{
	int i;
	for (i=0; i <= MAX; i++)
		printf("%ld ", v[i].num);
}
*/	

void le_vetor (struct racional v[], int n)
{
	int i, a = 0, b = 0;
	for (i=1; i <= n; i++)
		v[i] = cria_r(a, b);
}


//imprime todos os elementos do vetor sem espaco no final!!!
void imprime_vetor (struct racional v[], int n)
{
	int i;
	
	if (n <= 0)
		return;
		
	printf("VETOR= ");
	for (i=1; i <= (n-1); i++)
	{
		imprime_r(v[i]);
		printf(" ");
	}
	imprime_r(v[i]);
	printf("\n");
}


void elimina_nan (struct racional v[], int *n)
{
	int i = *n;
	
	while (i >= 1)
	{
		if (v[i].den == 0)
		{
			v[i] = v[*n];
			*n = *n - 1;
		}
		i--;
	}
}	


//select sort
void ordena_vetor (struct racional v[], int n)
{
	struct racional aux;
	int i, j, menor;
	
	for (i=1; i < n; i++)
	{
		//assume que a posicao inicial tem o menor valor
		menor = i;
		
		for (j=(i+1); j < n; j++)
		{
			//se o elemento atual eh menor que o menor anterior, atualiza a variavel 
			if (compara_r(v[menor], v[j]) == 1) 
				menor = j;	
		}
		
		//troca o elemento para o lugar correto
		aux = v[i];
		v[i] = v[menor];
		v[menor] = aux;
	}

}


void soma_vetor (struct racional v[], struct racional *soma, int n)
{
	int i;
	soma -> den = 1;
	for (i=1; i <= n; i++)
	{
		soma_r(v[i], *soma, soma);
	}
}


int main ()
{
	struct racional v[MAX], soma, *ptr_soma;
	int n, *ptr_n = &n;
	
	ptr_soma = &soma;
	
	scanf("%d", &n);
	
	le_vetor(v, n);
	imprime_vetor(v, n);
	
	elimina_nan(v, ptr_n);
	imprime_vetor(v, n);
	
	ordena_vetor(v, n);
	imprime_vetor(v , n);
	
	soma_vetor(v, ptr_soma, n);
	imprime_r(soma);
	
}

