#include "graphics.h"
#include <stdlib.h>
#include <stdio.h>

#define X_MAX getmaxwidth()
#define Y_MAX getmaxheight()
#define BORDERS 100
#define STEP 0.01

double func_exp(double x,double a,double b)
{
	return a*exp(b*x);
}

int main()
{
	FILE *f;
	f=fopen("input.txt","r");	
	int n=0;
	fscanf(f,"%d",&n);
	double *xs=(double *)calloc(n,sizeof(double));
	double *ys=(double *)calloc(n,sizeof(double));
	int i=0;
	for ( i=0;i<n;i++)
	{
		fscanf(f,"%lf",&xs[i]);
	}
	printf("\n");
	for ( i=0;i<n;i++)
	{
		fscanf(f,"%lf",&ys[i]);
	}
	fclose(f);
	double *lnys=(double *)calloc(n,sizeof(double));
	for ( i=0;i<n;i++)
	{
		lnys[i]=log(ys[i]);
	}
	double Mxx=0,Mx=0,Mxy=0,My=0;
	double swap;
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
	double b=(Mxx*My-Mx*Mxy)/(Mxx-Mx*Mx);
	swap=b;
	b=a;
	a=exp(swap);
	int window1,window2;
	window1=initwindow(getmaxwidth(),getmaxheight(),"MNQ");
	double x_max=xs[n-1],x_min=xs[0],max=0,min=0,a1=0,b1=0,ox=0,oy=0;
	double x=0;
	for ( i=0;i<n;i++)
	{
		if ( lnys[i]>max)
			max=ys[i];
		if ( lnys[i] <min)
			min=ys[i];
	}
	for ( x=x_min;x<x_max;x+=STEP)
	{
		if ( func_exp(x,a,b)>max)
			max=func_exp(x,a,b);
		if ( func_exp(x,a,b)<min)
			min=func_exp(x,a,b);
	}
	a1=(X_MAX-2*BORDERS)/(x_max-x_min);
	b1=(Y_MAX-2*BORDERS)/(max-min);
	b1=-b1; 
	ox =  BORDERS - a1 * x_min; 
	oy =  BORDERS - max*b1;
	rectangle(BORDERS,BORDERS,X_MAX-BORDERS,Y_MAX-BORDERS);
	setcolor(RED);
	setfillstyle(1,RED);
	double e=0;
	for (i=0;i<n;i++)
	{
		circle(a1*xs[i]+ox,b1*ys[i]+oy,5);
		floodfill(a1*xs[i]+ox+1,b1*ys[i]+oy,RED);
		e+=pow(func_exp(xs[i],a,b)-ys[i],2);
	}
	moveto(a1*x_min+ox,b1*func_exp(x_min,a,b)+oy);
	setcolor(BLUE);
	for (x=x_min;x<x_max;x+=STEP)
	{
		lineto(a1*x+ox,b1*func_exp(x,a,b)+oy);
		moveto(a1*x+ox,b1*func_exp(x,a,b)+oy);
	}
	double coor=0;
	char *num=(char *)malloc(sizeof(char));
	double i2=0;
	setcolor(WHITE);
	if ( (oy <= Y_MAX-BORDERS) && ( oy>= BORDERS) ) 
	{
		line(BORDERS,oy,X_MAX-BORDERS,oy);
		outtextxy(X_MAX - BORDERS+10, oy, "X");
		coor=BORDERS;
		i2=x_min;
		sprintf(num, "%.2f", i2);
		while (coor<X_MAX-BORDERS)
		{
			outtextxy(coor+10,oy+10,num);
			line(coor,oy-10,coor,oy+10);
			coor+=a1*(x_max-x_min)/10;
			i2+=(x_max-x_min)/10;
			sprintf(num, "%.2f", i2);
		}
	}
	else
	{
		line(BORDERS,Y_MAX-BORDERS,X_MAX-BORDERS,Y_MAX-BORDERS);
		outtextxy(X_MAX - BORDERS + 10, Y_MAX-BORDERS, "X");
		coor=ox;
		sprintf(num, "%.2f", i2);
		coor=BORDERS;
		i2=x_min;
		sprintf(num, "%.2f", i2);
		while (coor<X_MAX-BORDERS)
		{
			outtextxy(coor+10,Y_MAX-BORDERS+10,num);
			line(coor,Y_MAX-BORDERS-10,coor,Y_MAX-BORDERS+10);
			coor+=a1*(x_max-x_min)/10;
			i2+=(x_max-x_min)/10;
			sprintf(num, "%.2f", i2);
		}

	}
	if ( ( ox >= BORDERS) && ( ox <=X_MAX-BORDERS)) 
	{
		line(ox,BORDERS,ox,Y_MAX-BORDERS);
		outtextxy(ox - 10, BORDERS - 10, "Y");
		i2=max;
		coor=BORDERS;
		sprintf(num, "%.2f", i2);
		while (coor<Y_MAX-BORDERS)
		{
			outtextxy(ox+10,coor+10,num);
			line(ox-10,coor,ox+10,coor);
			coor-=b1*(max-min)/10;
			i2-=(max-min)/10;
			sprintf(num, "%.2f", i2);
		}
	}
	else
	{
		line(BORDERS,BORDERS,BORDERS,Y_MAX-BORDERS);
		outtextxy(BORDERS - 10, BORDERS - 15, "Y");
		i2=max;
		coor=BORDERS;
		sprintf(num, "%.2f", i2);
		while (coor<Y_MAX-BORDERS)
		{
			outtextxy(BORDERS+10,coor+10,num);
			line(BORDERS-10,coor,BORDERS+10,coor);
			coor-=b1*(max-min)/10;
			i2-=(max-min)/10;
			sprintf(num, "%.2f", i2);
		}
	}
	//system("pause");
	char buff[100]={0};
	char buff2[100]={0};
	window2=initwindow(X_MAX/5,Y_MAX/5,"about");
	setcurrentwindow(window2);
	strcat(buff,"e=");
	sprintf(buff2,"%.4lf",e);
	strcat(buff,buff2);
	outtextxy(0,0,buff);
	memset(buff,0,strlen(buff));
	strcat(buff,"f(x)=");//a
	sprintf(buff2,"%.4lf",a);
	strcat(buff,buff2);
	strcat(buff,"*exp(");
	sprintf(buff2,"%.4lf",b);
	strcat(buff,buff2);
	strcat(buff,"*x)");
	outtextxy(0,20,buff);
	system("pause");
	free(xs);
	free(ys);
	free(num);
	return 0;
}
