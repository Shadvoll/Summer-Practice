#include "graphics.h"
#include <stdlib.h>
#include <stdio.h>
/*8.	»меетс€ экспериментально полученна€ зависимость, представленна€ следующей таблицей:
xi	2	3	4	5	6	7	8	9	10	11	12	13	14
yi	6	9,3	10,2	11,5	12	12,7	13,2	14,1	15,4	15,7	15,6	16,1	17
ћетодом наименьших квадратов подобрать аппроксимирующую зависимость в виде экспоненциальной функции.

??? y=a*e^(bx)
*/
double lin(double x,double a,double b)
{
	return b+a*x;
}
double func_exp(double x,double a,double b)
{
	return a*exp(b*x);
}
#define X_MAX getmaxwidth()
#define Y_MAX getmaxheight()
#define BORDERS 100
#define STEP 0.1
int main()
{
	FILE *f;
	f=fopen("input.txt","r");	
	int n=0;
	fscanf(f,"%d",&n);
	//double *xs=(double *)calloc(n,sizeof(double));
	double xs[1000]={0};
	//double *ys=(double *)calloc(n,sizeof(double));
	double ys[1000]={0};
	int i=0;
	for ( i=0;i<n;i++)
	{
		fscanf(f,"%lf",&xs[i]);
		printf("%lf ",xs[i]);
	}
	printf("\n");
	for ( i=0;i<n;i++)
	{
		fscanf(f,"%lf",&ys[i]);
		printf("%lf ",ys[i]);
	}
	fclose(f);
	double *lnys=(double *)calloc(n,sizeof(double));
	for ( i=0;i<n;i++)
	{
		lnys[i]=log(ys[i]);
	}
	double Mxx=0,Mx=0,Mxy=0,My=0;
	for (i=0;i<n;i++)
	{
		Mxx+=xs[i]*xs[i];
		Mxy+=xs[i]*lnys[i];
		My+=lnys[i];
		Mx+=xs[i];
	}
	Mxx=Mxx/n;
	Mxy=Mxy/n;
	My=My/n;
	Mx=Mx/n;
	double a=(Mxy-My*Mx)/(Mxx-Mx*Mx);
	//a=exp(a);
	double b=(Mxx*My-Mx*Mxy)/(Mxx-Mx*Mx);
	initwindow(getmaxwidth(),getmaxheight(),"MNQ");
	//ln y=ln a +bx
	double x_max=xs[n-1],x_min=xs[0],max=0,min=0,a1=0,b1=0,ox=0,oy=0;
	double x=0;
	//for ( x=x_min;x<x_max;x+=STEP)
	for ( i=0;i<n;i++)
	{
		/*if ( lin(x,a,b)>max)
			max=lin(x,a,b);
		if ( lin(x,a,b)<min)
			min=lin(x,a,b);*/
		if ( lnys[i]>max)
			max=ys[i];
		if ( lnys[i] <min)
			min=ys[i];
	}
	for ( x=x_min;x<x_max;x+=STEP)
	{
		if ( lin(x,a,b)>max)
			max=lin(x,a,b);
		if ( lin(x,a,b)<min)
			min=lin(x,a,b);
	}
	a1=(X_MAX-2*BORDERS)/(x_max-x_min);
	b1=(Y_MAX-2*BORDERS)/(max-min);
	b1=-b1; 
	ox =  BORDERS - a1 * x_min; 
	oy =  BORDERS - max*b1;
	rectangle(BORDERS,BORDERS,X_MAX-BORDERS,Y_MAX-BORDERS);
	for (i=0;i<n;i++)
	{
		//putpixel(a1*xs[i]+ox,b1*ys[i]+oy,RED);
		circle(a1*xs[i]+ox,b1*lnys[i]+oy,5);
	}
	for (x=x_min;x<x_max;x+=STEP)
	{
		putpixel(a1*x+ox,b1*lin(x,a,b)+oy,WHITE);
		//circle(a1*xs[i]+ox,b1*ys[i]+oy,5);
	}
	system("pause");
	return 0;
}
/*”пражнение. ѕровести подобные рассуждени€ и сформулировать способ решени€ задачи дл€ функций вида y=aХe^(bx).
ƒл€ того, чтобы найти наилучшую функцию вида y=tХx^n, нужно прологарифмировать это соотношение.
ѕри этом получитс€ выражение: ln(y)=ln(t)+nХln(x), откуда и вытекает способ решени€:
Х	замен€ем в исходной таблице переменную x на u=ln(x);
Х	переменную y замен€ем на ln(y), а все числа, записанные в таблице, Ц на их логарифмы;
Х	дл€ получившейс€ таблицы находим коэффициенты a и b линейной зависимости;
Х	по получившимс€ значени€м a и b находим нужные нам коэффициенты, примен€€ формулы n=а, t=e^b.
*/
