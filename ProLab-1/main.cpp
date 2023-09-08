#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <dos.h>

int factorial(int n)
{
    if(n==0)
        return 1;
    else

    return (n*factorial(n-1));


}
int combination(int n, int r)
{
    return (factorial(n)/(factorial(n-r)*factorial(r)));
}

int main()
{
    FILE *txt;
    txt = fopen("C:\\Users\\Kaank\\Desktop\\Coordinates.txt","r");
    if(txt==NULL)
    {
        printf("Dosyaya erisilemedi!");//Txt dosyaniz yok ise açmayacaktir.
        exit(1);
    }
//txt dosyamdan koordinatlari alabilmek icin txt yi string dizisine atadim.
    char txtToStr[999];

    fgets(txtToStr,999,txt);

    fclose(txt);
//x ve y  koordinatlarini atayacagimiz dizimizin boyutunu belirleyelim.

    int numbers_Of_xyCrdnt=0;
    int tim=0;
    printf("Giris:\n\n");
    while (txtToStr[tim])//n kez
    {
        printf("%c", txtToStr[tim]);//n kez

        if(txtToStr[tim]=='(' || txtToStr[tim]==')')
            numbers_Of_xyCrdnt++;
        tim++;
    }

    //koordinat noktalarini yazacagimiz dizimizi tanimlayalim ve her indexini 0(sifir) a esitleyelim.
    int crdnates[numbers_Of_xyCrdnt];
    int i;
    for(i=0; i<numbers_Of_xyCrdnt; i++)
    {
        crdnates[i]=0;
    }

//string dizisinin icinden de x ve y koordinatlarimi alabilmek icin integer turunde bir diziye cevirecegim.
    int j=0;
    int k=0;

    while(txtToStr[k]!='\0')
    {
        if(isdigit(txtToStr[k]) && txtToStr[k-1] != '-' && crdnates[j] >=0)
        {
            crdnates[j]=crdnates[j] * 10 + (txtToStr[k] - 48);
        }
        if((isdigit(txtToStr[k]) && txtToStr[k-1] =='-') ||(isdigit(txtToStr[k]) && crdnates[j] < 0))
        {
            crdnates[j]=crdnates[j] * 10 - (txtToStr[k] - 48);
        }
        if((txtToStr[k]==',' && isdigit(txtToStr[k+1])) || (txtToStr[k-1]==',' && txtToStr[k]=='(' &&isdigit(txtToStr[k+1])) || (txtToStr[k-1]==',' && txtToStr[k]=='(' && txtToStr[k+1] =='-') || (txtToStr[k]==',' && txtToStr[k+1]=='-'))
        {
            j++;
        }
        k++;
    }
//x ve y koordinatlarini 2 ayri diziye ayirdik. Ve atamasini yaptik.
    int x_coordinates[numbers_Of_xyCrdnt/2];
    int y_coordinates[numbers_Of_xyCrdnt/2];

    int a,b=0,c=0;

    for(a=0; a<numbers_Of_xyCrdnt; a++)
    {
        if((a%2)==0)
        {
            x_coordinates[b]= crdnates[a];
            b++;
        }
        else
        {
            y_coordinates[c]= crdnates[a];
            c++;
        }
    }
// iki nokta arasi maximum urakligi burada hesapliyoruz.
    float v,maxi=0;//1kez.
    int tt,qq;


    for(tt=0; tt<numbers_Of_xyCrdnt/2-1; tt++)//tt 1 kez çalışır.  tt<n-1  n kez çalısır, tt++ n-1 kez calisir. -- 2n
    {
        for(qq=tt+1; qq<numbers_Of_xyCrdnt/2; qq++) //qq=tt+1 1 kez calisacak.  qq<n n+1 kez calisacak. qq++ n kez -- (2n+2)*(n-1) -- 2n^2-2
        {
            v = fabs(sqrt((pow(x_coordinates[tt]-x_coordinates[qq],2))+(pow(y_coordinates[tt]-y_coordinates[qq],2))));//(n-1).n kez calisacak.

            if(v>maxi)//worst case durumu için [(n-1).n-1] kez calisir.
            {
                maxi = v;//worst case den dolayı buda [(n-1).n-1] kez calisir. toplam :
            }

        }
    }
//Maksimum uzaklik hangi noktalar arasinda onu buluyoruz. Ve o noktalari x ve y dizilerine atiyoruz.
    float z;
    int ii,jj,kk=0,ll=0;//kk=0 için 1 kez ll=0 için 1 kez.
    float x_coord[999];
    float y_coord[999];
    float radius;
    float center_x,center_y;

    for(ii=0; ii<(numbers_Of_xyCrdnt/2)-1; ii++)//ii=0 için 1 kez. ii<n için n+1 kez .i++ için n kez. toplam : 2n+2 kez.
    {
        for(jj=ii+1; jj<numbers_Of_xyCrdnt/2; jj++)//jj=ii+1 için 1 kez. jj<n+1 (çünkü bir üstteki for ile aynı döngü sayısına tekabül ediyor n+1 kez. j++ n kez.toplam: n.(2n+2)
        {
            z = (sqrt((pow(x_coordinates[ii]-x_coordinates[jj],2))+(pow(y_coordinates[ii]-y_coordinates[jj],2)))); //n.n kez.

            if(z == maxi)//n.n kez
            {
                x_coord[kk]=(float)x_coordinates[ii];//worst case den dolayı aşağıdaki bütün atamalar tek tek n.n kez calısır.
                kk++;
                x_coord[kk]=(float)x_coordinates[jj];
                kk++;
                y_coord[ll]=(float)y_coordinates[ii];
                ll++;
                y_coord[ll]=(float)y_coordinates[jj];
                ll++;

            }
        }
    }
// Burada islemimizin step 1 de kalarak step1 i kullanmasini ya da step2 ye geçmesinin gerekli olup olmadigini hesapliyoruz.
    int nnn;
    radius = maxi / 2;
    float radius1 = radius;
    center_x = (x_coord[0] + x_coord[1]) /2;
    center_y = (y_coord[0] + y_coord[1]) /2;

//bu dongu belirlenen ilk cemberimizin merkezinin girilen koordinatlarimiza uzakligini olcuyor buna gore stepleri belirliyoruz.
    float zz,farPx,farPy;
    for(ii=0; ii<(numbers_Of_xyCrdnt/2); ii++)
    {

        zz = (sqrt((pow(center_x-x_coordinates[ii],2))+(pow(center_y-y_coordinates[ii],2))));
        if(zz>radius1)
        {
            farPx=x_coordinates[ii];
            farPy=y_coordinates[ii];
            radius1 = zz;
        }
    }
    //Ýslemimizin sonucuna göre girilen noktalarin merkez noktasina uzakligi yaricaptan kucuk veya esit ise  step1 e  uygun olup buradaki kosulumuza girecektir. Ve cemberimizi cizecektir.

    if(radius1<=radius)
    {
        int mmm;
        float xt,yt;
        printf("\n\nCikti:");
        printf("\n\ncenter : (%.2f , %.2f)\n",center_x,center_y);
        printf("radius : %f\n",radius);
        //arayuz boyutumuzu ve cemberimizi cizdiriyoruz.
        initwindow(1000,1000,"");
        setcolor(WHITE);
        circle(500+(25 * center_x),500-(25 * center_y),25 * radius);
        //koordinat duzlemimizin cizgisini cizdiriyoruz.
        for(mmm=0; mmm<1000; mmm+=25)
        {
            if(mmm==500)
            {
                setcolor(WHITE);
                line(mmm,0,mmm,1000);
                line(0,mmm,1000,mmm);
            }
            else
            {
                setcolor(DARKGRAY);
                line(mmm,0,mmm,1000);
                line(0,mmm,1000,mmm);
            }
        }
        //merkez noktamizi cizdiriyoruz.
        setcolor(YELLOW);
        circle(500+(25 * center_x),500-(25 * center_y),6);
        setfillstyle(SOLID_FILL,YELLOW);
        floodfill(500+(25 * center_x),500-(25 * center_y),YELLOW);
        //koordinat duzlemimizdeki birimlerimizi cizdiriyoruz.
        for(mmm=0; mmm<1000; mmm+=25)
        {
            setcolor(WHITE);
            circle(mmm,500,5);
            setfillstyle(SOLID_FILL,WHITE);
            floodfill(mmm,500,WHITE);
            circle(500,mmm,5);
            setfillstyle(SOLID_FILL,WHITE);
            floodfill(500,mmm,WHITE);

        }
        //koordinat duzleminde girmis oldugumuz koordinatlarimizi cizdiriyoruz.
        for(mmm =0 ; mmm < (numbers_Of_xyCrdnt)/2 ; mmm++)
        {
            setcolor(LIGHTBLUE);
            circle(500+(25 * x_coordinates[mmm]),500-(25 * y_coordinates[mmm]),5);
            setfillstyle(SOLID_FILL,LIGHTBLUE);
            floodfill(500+(25 * x_coordinates[mmm]),500-(25 * y_coordinates[mmm]),LIGHTBLUE);
        }
        //cemberimin yaricap cizgisini cizdiriyorum.
        setcolor(LIGHTMAGENTA);
        line(500+(25*center_x),500-(25*center_y),500+(25*(center_x+radius)),500-(25*center_y));

        //Bernstein Polinomu
        float u;
        int n= (numbers_Of_xyCrdnt)/2-1;

        for(u=0; u<1; u+=0.0001)
        {
            xt=0;
            yt=0;

            for (i=0; i<=n; i++)
            {
                xt = xt + (combination(n,i) * pow(1-u,n-i) * pow(u,i) * x_coordinates[i]);
                yt = yt + (combination(n,i) * pow(1-u,n-i) * pow(u,i) * y_coordinates[i]);


            }
            putpixel (500+25*xt, 500-25*yt, WHITE);
        }
        getch();
        closegraph();
        //yukaridaki merkezin noktalara olan uzakligi islemimizin sonucu yaricaptan buyuk ise islemimiz step2 ye girmek zorunda kalýp buradaki kosulumuza girecektir. Ve cemberimizi cizecektir.

    }
    if(radius1 > radius)
    {
        //burada ilk cemberimizin merkez koordinatlari ve hesapladigimiz merkeze en uzak noktanin x ,y degerleri ile iþleme girip yeni merkezimizin koordinatlarini belirliyoruz.
        float x,y,r,xt,yt;
        int mmm;
        x = (0.5)*((((pow(x_coord[0],2)+pow(y_coord[0],2))*(farPy-y_coord[1])) + ((pow(x_coord[1],2)+pow(y_coord[1],2))*(y_coord[0]-farPy))+((pow(farPx,2)+pow(farPy,2))*(y_coord[1]-y_coord[0]))) / (x_coord[0]*(farPy-y_coord[1])+(x_coord[1]*(y_coord[0]-farPy))+(farPx*(y_coord[1]-y_coord[0]))));
        y = (0.5)*((((pow(x_coord[0],2)+pow(y_coord[0],2))*(farPx-x_coord[1])) + ((pow(x_coord[1],2)+pow(y_coord[1],2))*(x_coord[0]-farPx))+((pow(farPx,2)+pow(farPy,2))*(x_coord[1]-x_coord[0]))) / (y_coord[0]*(farPx-x_coord[1])+(y_coord[1]*(x_coord[0]-farPx))+(farPy*(x_coord[1]-x_coord[0]))));
        r = (sqrt((pow(x-x_coord[0],2))+(pow(y-y_coord[0],2))));

        printf("\n\nCikti:");
        printf("\ncenter : (%.2f , %.2f)\n",x,y);
        printf("radius : %f\n",r);
        //arayüz boyutunu ve cemberimizi cizdiriyoruz.
        initwindow(1000,1000,"");
        setcolor(WHITE);
        circle(500+(25 * x),500-(25 * y),25 * r);
        //koordinat duzlemimizin cizgisini cizdiriyoruz.
        for(mmm=0; mmm<1000; mmm+=25)
        {
            if(mmm==500)
            {
                setcolor(WHITE);
                line(mmm,0,mmm,1000);
                line(0,mmm,1000,mmm);
            }
            else
            {
                setcolor(DARKGRAY);
                line(mmm,0,mmm,1000);
                line(0,mmm,1000,mmm);
            }
        }
        //merkez noktamizi cizdiriyoruz.
        setcolor(YELLOW);
        circle(500+(25 * x),500-(25 * y),6);
        setfillstyle(SOLID_FILL,YELLOW);
        floodfill(500+(25 * x),500-(25 * y),YELLOW);
        //koordinat duzlemimizdeki birimlerimizi cizdiriyoruz.
        for(mmm=0; mmm<1000; mmm+=25)
        {
            setcolor(WHITE);
            circle(mmm,500,5);
            setfillstyle(SOLID_FILL,WHITE);
            floodfill(mmm,500,WHITE);
            circle(500,mmm,5);
            setfillstyle(SOLID_FILL,WHITE);
            floodfill(500,mmm,WHITE);
        }
        //koordinat duzleminde girmis oldugumuz koordinatlarimizi cizdiriyoruz.
        for(mmm =0 ; mmm < (numbers_Of_xyCrdnt)/2 ; mmm++)
        {
            setcolor(LIGHTBLUE);
            circle(500+(25 * x_coordinates[mmm]),500-(25 * y_coordinates[mmm]),5);
            setfillstyle(SOLID_FILL,LIGHTBLUE);
            floodfill(500+(25 * x_coordinates[mmm]),500-(25 * y_coordinates[mmm]),LIGHTBLUE);
        }
        //cemberimin yaricap cizgisini cizdiriyorum.
        setcolor(LIGHTMAGENTA);
        line(500+(25*x),500-(25*y),500+(25*(x+r)),500-(25*y));
//Bersntein Polinomu
        float u;
        int n= (numbers_Of_xyCrdnt)/2-1;                                                      //1 kez

        for(u=0; u<1; u+=0.0001)                                                             //u=0 1 kez.  u<n  10.001 kez u+=  10.000 kez  toplam : 10.002 kez
        {
            xt=0;                                                                             // 10.000 kez
            yt=0;                                                                             // 10.000 kez

            for (i=0; i<=n; i++)                                                           //i=0 1 kez i<=n n+2 kez  i++ n+1 kez toplam : (2n+4)*(10.000)
            {
                xt = xt + (combination(n,i) * pow(1-u,n-i) * pow(u,i) * x_coordinates[i]); //10.000(n+1)
                yt = yt + (combination(n,i) * pow(1-u,n-i) * pow(u,i) * y_coordinates[i]); //10.000(n+1)
            }
            putpixel (500+25*xt, 500-25*yt, WHITE);
        }
        getch();
        closegraph();
    }

    return 0;
}
