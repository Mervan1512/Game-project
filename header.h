#ifndef HEADER_H_
#define HEADER_H_
#include <iostream>
#include <fstream>
#include <string>
#include "header.h"
using namespace std;



char map[100][100];
char hayaletYan1='1';
char hayaletYan2='1';
char hayaletYan3='1';
char hayaletYanY='1';
int meyveSayisi;
int startTime=600;
int diskSay=0;
int hayaletSayisi=3;
int bekleyenHayaletSayisi=0;
int bekleyenHayaletler[3][2]={{0,0},{0,0},{0,0}}; // ilk index hayalet beklemede mi?, ikinci index beklemedeki s�resi
int pacmanHayaletUstundeKord[1][2];
int beklemeKordinatlari[3][2];
int diskSayisi=0;
int hak=3;
int kacMeyveYiyildi=0;
int kacHayaletYiyildi=0;
int baslangicDiskSayisi=0;
bool diskSayilsinMi=false;
bool meyveYedinMi=false;
bool h1HareketEttiMi=false;
bool h2HareketEttiMi=false;
bool h3HareketEttiMi=false;
bool pacmanHayaletUstunde=false;
bool bulundu=false;
bool meyveOlustuMu=false;
bool hayaletGorduMu=false;
int mX,mY;
string yon1="sag",yon2="yukari",yon3="sol";
int pacmanKordinat[1][2];


template <class T> 
class Node
{
	public: 
	Node(const T& veri = T(),Node<T>* sonraki = NULL)
	{
		this->veri=veri;
		this->sonraki=sonraki;
	} 
	T veri; // de�erimiz
	Node<T>* sonraki; // bir sonraki de�eri g�steren pointer
};

template <class T> 
class list
{
	Node<T>* kok;
	public:
		list() : kok(NULL){} // Listeyi bo� olarak ba�latt�k
		Node<T>* bas() // listenin ba��n� g�sterir
		{
			return kok;
		}
		Node<T>* son() // listenin sonunu g�sterir
		{
			return NULL;
		}
		bool isEmpty() // liste bo� mu
		{
			return kok == NULL;
		}
		void push_back(const int value) // listeye sondan eleman ekler
		{
			if(isEmpty())
			{
				kok = new Node<T>(value);
			}
			else
			{
				Node<T>* tmp = bas();
				while(tmp->sonraki != son())
				{
					tmp=tmp->sonraki;
				}
				tmp->sonraki=new Node<T>(value);	
			}	
				
		}
		void push_front(const int value)
		{
			Node<T>* tmp= new Node<T>(value);
			tmp->sonraki = kok;
			kok=tmp;
			
		}
		void pop_back()
		{
			if(isEmpty())
			{
				throw "Error: list is empty";
			}
			if(bas()->sonraki==son())
			{
				delete kok;
				kok=NULL;
			}
			else
			{
				Node<T>* tmp=bas();
				while(tmp->sonraki->sonraki != son())
				{
					tmp = tmp-> sonraki;
				}
				delete tmp-> sonraki;
				tmp->sonraki=NULL;
			}
		}
		void pop_front()
		{
			if(isEmpty())
			{
				throw "Error: list is empty";
			}
			Node<T>* tmp = kok;
			kok = tmp->sonraki;
			delete tmp;
		}
		
		int size()
		{
			int counter = 0;
			Node<T>* tmp = bas();
			while(tmp!= son())
			{
				tmp=tmp->sonraki;
				counter++;
			}
			return counter;
		}
		
		T front()
		{
			if(isEmpty())
				throw "list is empty";
			return bas()->veri;	
		}	
		
};

template <class T>
class Stack:private list<T>
{
	public:
		Stack()	: list<T>(){} 
		bool isEmpty()
		{
			return list<T>::isEmpty();
		}
		void push(const T& value)
		{
			list<T>::push_front(value);
		}
		void pop()
		{
			list<T>::pop_front();
		}
		int size()
		{
			return list<T>::size();
		}
};

template <class T>
class Queue:private list<T> 
{
	public:
		bool isEmpty()
		{
			return list<T>::isEmpty();
		}
		void enqueue(const T& value)
		{
			list<T>::push_back(value);
		}
		void dequeue()
		{
			list<T>::pop_front();
		}
			int size()
		{
			return list<T>::size();
		}
		T front()
		{
			return list<T>::front();
		}
};




void sureHesapla(char hangisi) // ba�lang�� s�resi 600, her harekette -1 sn, meyve +5 sn, hayalet -10 sn, N normal, H hayalet, M meyve
{
	if(hangisi=='N')
	{
		startTime-=1;
	}
	else if(hangisi=='H')
	{
		hayaletGorduMu=true;
		startTime-=10;
		hak--;
	}
	else if(hangisi=='M')
	{
		startTime+=5;
	}
}

int haritaBoyutu() // metin belgesi �zerinden haritan�n boyutunu tespit eder �rne�in 25x25 lik harita
{
	ifstream dosya("pacman.txt"); // dosya okuma i�lemi i�in
	string metin; // okunan karakterleri atayaca��m�z string
 	getline(dosya,metin);
 	int boyut = metin.size()-metin.size()/2; // burda s�tunlar�n say�s�n� buluyoruz ancak kare bir haritaya bakt���m�z i�in sat�r say�s�da ayn�d�r.
	dosya.close();
	return boyut;
}

int meyveSayisiBul() // metin belgesi �zerinden meyve say�s�n� bulur
{
	ifstream dosya("pacman.txt"); // dosya okuma i�lemi i�in
	string metin; // okunan karakterleri atayaca��m�z string
	int meyveSayisi=0;
 	for(int i=0;i<haritaBoyutu();i++)
 	{
 		for(int j=0;j<haritaBoyutu();j++)
 		{
 		
 			getline(dosya,metin,',');
 			if(metin.length()>1)
 			{
				if(metin[0]=='2')
				{
					meyveSayisi++;
				}
				if(metin[2]=='2')
				{
					meyveSayisi++;
				}
				i++;
				j=0;
				if(i>=haritaBoyutu())
 				{
 					break;
				}
			}
			else
			{
				if(metin[0]=='2')
				{
					meyveSayisi++;
				}
			}
    		
	 	}
	}
	dosya.close();
	return meyveSayisi;
}

void diskSayisiBul()
{
	ifstream dosya("pacman.txt"); // dosya okuma i�lemi i�in
	string metin; // okunan karakterleri atayaca��m�z string
 	for(int i=0;i<haritaBoyutu();i++)
 	{
 		for(int j=0;j<haritaBoyutu();j++)
 		{
 		
 			getline(dosya,metin,',');
 			if(metin.length()>1)
 			{
				if(metin[0]=='1')
				{
					diskSayisi++;
				}
				if(metin[2]=='1')
				{
					diskSayisi++;
				}
				i++;
				j=0;
				if(i>=haritaBoyutu())
 				{
 					break;
				}
			}
			else
			{
				if(metin[0]=='1')
				{
					diskSayisi++;
				}
			}
    		
	 	}
	}
	baslangicDiskSayisi=diskSayisi;
	dosya.close();
}

void oyunAlaniOku() // metin belgesi �zerinden oyun alan� bilgileri okuduk ve map dizisine aktard�k
{
	ifstream dosya("pacman.txt"); // dosya okuma i�lemi i�in
	string metin; // okunan karakterleri atayaca��m�z string
 	for(int i=0;i<haritaBoyutu();i++)
 	{
 		for(int j=0;j<haritaBoyutu();j++)
 		{
 			getline(dosya,metin,',');
 			if(metin.length()>1 && metin.length()<=3)
 			{
 				map[i][j]=metin[0];
 				i++;
 				j=0;
 				map[i][j]=metin[2];

 				if(i>=haritaBoyutu()) // haritan�n alt taraflar�ndaki bo� (endl) k�s�mlar�n� okumas�n diye
 				{
 					break;
				}
			}
			else
			{
				map[i][j]=metin[0];
				
			}
	 	}
	}
	dosya.close();
}

void mapYazdir(int hayaletKordinatlari[3][2],int meyveKordinatlari[100][2],int pacmanKordinat[1][2]) // map dizisinden , meyvelerin, hayaletlerin ve pacmanin konumu belirlenecek
{
	int meyveSirasi=0;
 	for(int i=0;i<haritaBoyutu();i++)
 	{
 		for(int j=0;j<haritaBoyutu();j++)
 		{
 				if(map[i][j]=='2')
				{
					meyveKordinatlari[meyveSirasi][0]=i;
					meyveKordinatlari[meyveSirasi][1]=j;
					meyveSirasi++;
				}
				if(map[i][j]=='3'|| map[i][j]=='4'|| map[i][j]=='5')
				{
					if(map[i][j]=='3')
					{
						hayaletKordinatlari[0][0]=i;
						hayaletKordinatlari[0][1]=j;
					}
					else if(map[i][j]=='4')
					{
						hayaletKordinatlari[1][0]=i;
						hayaletKordinatlari[1][1]=j;
					}
					else if(map[i][j]=='5')
					{
						hayaletKordinatlari[2][0]=i;
						hayaletKordinatlari[2][1]=j;
					}
				}
				
				if(map[i][j]=='9')
				{
					pacmanKordinat[0][0]=i;
					pacmanKordinat[0][1]=j;
				}	
		}
	}
}

void meyveOlustur(Queue<int>& meyveQKordinatlari)
{
	if(diskSayilsinMi==true)
	{
		diskSay++;
		if(diskSay==10)
		{
			meyveOlustuMu=true;
			mX=meyveQKordinatlari.front();
			meyveQKordinatlari.dequeue();
			mY=meyveQKordinatlari.front();
			meyveQKordinatlari.dequeue();
			
			map[mX][mY]='2';
			diskSay=0;
			if(meyveQKordinatlari.size()==0) // e�er ki yi�ilmi� meyve kalmad�ysa
			{
				diskSayilsinMi=false;
			}
			
		}
	}
}

void hayaletBeklet(int hayaletKordinatlari[3][2])
{
	
	for(int i=0; i < 3 ;i++)
	{
		BASADON:
		if(i==0)
		{
			if(bekleyenHayaletler[0][0]==1) // zaten beklemedeysem
			{
				i++;
				goto BASADON;
			}
			else // beklemede de�ilsem
			{
				if(bekleyenHayaletler[1][0]==1 && bekleyenHayaletler[2][0]==1)
				{
					if(bekleyenHayaletler[1][1] > bekleyenHayaletler[2][1])
					{
						bekleyenHayaletler[0][1]=bekleyenHayaletler[1][1]+5;
					}
					else
					{
						bekleyenHayaletler[0][1]=bekleyenHayaletler[2][1]+5;
					}
				}
				else if(bekleyenHayaletler[1][0]==1)
				{
					bekleyenHayaletler[0][1]=bekleyenHayaletler[1][1]+5;
				}
				else if(bekleyenHayaletler[2][0]==1)
				{
					bekleyenHayaletler[0][1]=bekleyenHayaletler[2][1]+5;
				}
				else
				{
					bekleyenHayaletler[0][1]=5;
				}
				bekleyenHayaletler[0][0]=1; // bekledi�imi g�sterdim
				beklemeKordinatlari[i][0]=hayaletKordinatlari[i][0]; //hayaletin i kordinat�n� kaydettik
				beklemeKordinatlari[i][1]=hayaletKordinatlari[i][1]; //hayaletin j kordinat�n� kaydettik
				map[hayaletKordinatlari[i][0]][hayaletKordinatlari[i][1]]=hayaletYan1; // hayaletin konumuna en son neyin �zerindeyse koyuyoruz
			}
		}
		
		else if(i==1)
		{
			if(bekleyenHayaletler[1][0]==1) // zaten beklemedeysem
			{
				i++;
				goto BASADON;
			}
			else // beklemede de�ilsem
			{
				if(bekleyenHayaletler[0][0]==1 && bekleyenHayaletler[2][0]==1)
				{
					if(bekleyenHayaletler[0][1] > bekleyenHayaletler[2][1])
					{
						bekleyenHayaletler[1][1]=bekleyenHayaletler[0][1]+5;
					}
					else
					{
						bekleyenHayaletler[1][1]=bekleyenHayaletler[2][1]+5;
					}
				}
				else if(bekleyenHayaletler[0][0]==1)
				{
					bekleyenHayaletler[1][1]=bekleyenHayaletler[0][1]+5;
				}
				else if(bekleyenHayaletler[2][0]==1)
				{
					bekleyenHayaletler[1][1]=bekleyenHayaletler[2][1]+5;
				}
				else
				{
					bekleyenHayaletler[1][1]=5;
				}
				bekleyenHayaletler[1][0]=1; // bekledi�imi g�sterdim
				beklemeKordinatlari[i][0]=hayaletKordinatlari[i][0]; //hayaletin i kordinat�n� kaydettik
				beklemeKordinatlari[i][1]=hayaletKordinatlari[i][1]; //hayaletin j kordinat�n� kaydettik
				map[hayaletKordinatlari[i][0]][hayaletKordinatlari[i][1]]=hayaletYan2; // hayaletin konumuna en son neyin �zerindeyse koyuyoruz
			}
		}
		
		else if(i==2)
		{
			if(bekleyenHayaletler[2][0]==1) // zaten beklemedeysem
			{
				break;
			}
			else // beklemede de�ilsem
			{
				if(bekleyenHayaletler[1][0]==1 && bekleyenHayaletler[0][0]==1)
				{
					if(bekleyenHayaletler[1][1] > bekleyenHayaletler[0][1])
					{
						bekleyenHayaletler[2][1]=bekleyenHayaletler[1][1]+5;
					}
					else
					{
						bekleyenHayaletler[2][1]=bekleyenHayaletler[0][1]+5;
					}
				}
				else if(bekleyenHayaletler[1][0]==1)
				{
					bekleyenHayaletler[2][1]=bekleyenHayaletler[1][1]+5;
				}
				else if(bekleyenHayaletler[0][0]==1)
				{
					bekleyenHayaletler[2][1]=bekleyenHayaletler[0][1]+5;
				}
				else
				{
					bekleyenHayaletler[2][1]=5;
				}
				bekleyenHayaletler[2][0]=1; // bekledi�imi g�sterdim
				beklemeKordinatlari[i][0]=hayaletKordinatlari[i][0]; //hayaletin i kordinat�n� kaydettik
				beklemeKordinatlari[i][1]=hayaletKordinatlari[i][1]; //hayaletin j kordinat�n� kaydettik
				map[hayaletKordinatlari[i][0]][hayaletKordinatlari[i][1]]=hayaletYan3; // hayaletin konumuna en son neyin �zerindeyse koyuyoruz
			}
		}
		
	}	
}

void hayaletHareket(int hayaletKordinatlari[3][2]) 
{
	// 1. HAYALET ���N SA� SOL KONTROL� START 
	
	// 1. HAYALET BEKLEMEDE DE��LSE
	if(bekleyenHayaletler[0][0]==0)
	{	// YA SA�IMDA PACMAN VARSA?
		
		// 1. HAYALET SA� KONTROL� START
		SAG1:
		if(h1HareketEttiMi==false && yon1=="sag" && map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]+1]!='0') // sa�da duvar yoksa
		{
			if(map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]+1]=='4') // sa��mdaki 2. hayaletse
			{
				if(h2HareketEttiMi==false)
				{
					if(yon2=="yukari"&& map[ hayaletKordinatlari[0][0]-1 ] [ hayaletKordinatlari[0][1]+1]!='0') // 2. hayalet yukar� ��k�yorsa ve yukarda duvar yoksa
					{
						hayaletYanY=hayaletYan2;
						hayaletYan2=map[ hayaletKordinatlari[0][0]-1 ] [ hayaletKordinatlari[0][1]+1]; // 2. hayalet i�in yukardakini kaydet
						map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]]=hayaletYan1;
						hayaletYan1=hayaletYanY;
						map[ hayaletKordinatlari[0][0]-1 ] [ hayaletKordinatlari[0][1]+1]='4'; // 2. hayaleti yukar�ya yaz
						map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]+1]='3'; // sa�a beni yaz
					}
					else if(yon2=="yukari"&& map[ hayaletKordinatlari[0][0]-1 ] [ hayaletKordinatlari[0][1]+1]=='0') // 2. hayalet yukar� ��k�yorsa ve yukarda duvar varsa
					{
						yon2="asagi";
						hayaletYanY=hayaletYan2;
						hayaletYan2=map[ hayaletKordinatlari[0][0]+1 ] [ hayaletKordinatlari[0][1]+1]; // 2. hayalet i�in a�a��dakini kaydet
						map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]]=hayaletYan1;
						hayaletYan1=hayaletYanY;
						map[ hayaletKordinatlari[0][0]+1 ] [ hayaletKordinatlari[0][1]+1]='4'; // 2. hayaleti a�a��ya yaz
						map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]+1]='3'; // sa�a beni yaz
					}
					
					else if(yon2=="asagi"&& map[ hayaletKordinatlari[0][0]+1 ] [ hayaletKordinatlari[0][1]+1]!='0') // 2. hayalet a�a�� iniyorsa ve a�a��da duvar yoksa
					{
						hayaletYanY=hayaletYan2;
						hayaletYan2=map[ hayaletKordinatlari[0][0]+1 ] [ hayaletKordinatlari[0][1]+1]; // 2. hayalet i�in yukardakini kaydet
						map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]]=hayaletYan1;
						hayaletYan1=hayaletYanY;
						map[ hayaletKordinatlari[0][0]+1 ] [ hayaletKordinatlari[0][1]+1]='4'; // 2. hayaleti yukar�ya yaz
						map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]+1]='3'; // sa�a beni yaz
					}
					else if(yon2=="asagi"&& map[ hayaletKordinatlari[0][0]+1 ] [ hayaletKordinatlari[0][1]+1]=='0') // 2. hayalet a�a�� iniyorsa ve a�a��da duvar varsa
					{
						yon2="yukari";
						hayaletYanY=hayaletYan2;
						hayaletYan2=map[ hayaletKordinatlari[0][0]-1 ] [ hayaletKordinatlari[0][1]+1]; // 2. hayalet i�in yukardakini kaydet
						map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]]=hayaletYan1;
						hayaletYan1=hayaletYanY;
						map[ hayaletKordinatlari[0][0]-1 ] [ hayaletKordinatlari[0][1]+1]='4'; // 2. hayaleti yukar�ya yaz
						map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]+1]='3'; // sa�a beni yaz
					}
					h1HareketEttiMi=true;	
					h2HareketEttiMi=true;	
				}
				
				else //sa��mdaki 2. hayaletse ve haraket etmemi�se
				{
					map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]]=hayaletYan1;
					hayaletYan1='4';
					map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]+1]='3'; // sa�a beni yaz
					h1HareketEttiMi=true;	
				}
				
			}
			
			else if(map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]+1]=='5') // sa��mdaki 3. hayaletse
			{
				if(h3HareketEttiMi==false )
				{
					if(yon3=="sol") // 3. hayalet sola gidiyorsa
					{
						hayaletYanY=hayaletYan3; // hayalet yan3� kaydettim
						hayaletYan3=hayaletYan1; // bulundu�um noktan�n kordinat�n� 3. hayaletin yan kordinat�na aktard�m
						hayaletYan1=hayaletYanY; 
						map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]]='5'; // bulundu�um konuma 3. hayaleti yaz
						map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]+1]='3'; // sa�a beni yaz
					}
					else if(yon3=="sag"&& map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]+2]=='0') // 2. hayalet yukar� ��k�yorsa ve yukarda duvar varsa
					{
						yon3="sol";
						hayaletYanY=hayaletYan3; // hayalet yan3� kaydettim
						hayaletYan3=hayaletYan1; // bulundu�um noktan�n kordinat�n� 3. hayaletin yan kordinat�na aktard�m
						hayaletYan1=hayaletYanY; 
						map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]]='5'; // bulundu�um konuma 3. hayaleti yaz
						map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]+1]='3'; // sa�a beni yaz
					}
				
					else if(yon3=="sag"&& map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]+2]!='0') // 2. hayalet a�a�� iniyorsa ve a�a��da duvar yoksa
					{
						hayaletYan1=hayaletYan3;
						hayaletYan3=map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]+2]; // 2. hayalet i�in yukardakini kaydet
						map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]+2]='5'; // 2. hayaleti yukar�ya yaz
						map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]+1]='3'; // sa�a beni yaz
					}
					h1HareketEttiMi=true;	
					h3HareketEttiMi=true;	
						
				}
				else //sa��mdaki 3. hayaletse ve haraket etmemi�se
				{
					map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]]=hayaletYan1;
					hayaletYan1='5';
					map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]+1]='3'; // sa�a beni yaz
					h1HareketEttiMi=true;	
				}		
				
			}
			
			else // sa�da duvar yoksa ve sa��mdaki hayalet de�ilse
			{
				map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]]=hayaletYan1; // yerime �ncekini yaz
				hayaletYan1=map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]+1]; // sa�dakini kaydet
				map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]+1]='3'; // sa�a beni yaz
				h1HareketEttiMi=true;	
			}
		}
		
		else if(h1HareketEttiMi==false && yon1=="sag" && map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]+1]=='0') // y�n�m sa� ise sa�da duvar varsa 
		{
			yon1="sol";
			goto SOL1;
		}
		
		// 1. HAYALET SA� KONTROL� END
		
		// 1. HAYALET SOL KONTROL� START
		SOL1:
		if(h1HareketEttiMi==false && yon1=="sol" && map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]-1]!='0') // sa�da duvar yoksa
		{
			
			if(map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]-1]=='4') // sa��mdaki 2. hayaletse
			{
				if(h2HareketEttiMi==false)
				{
					if(yon2=="yukari"&& map[ hayaletKordinatlari[0][0]-1 ] [ hayaletKordinatlari[0][1]-1]!='0') // 2. hayalet yukar� ��k�yorsa ve yukarda duvar yoksa
					{
						hayaletYanY=hayaletYan2;
						hayaletYan2=map[ hayaletKordinatlari[0][0]-1 ] [ hayaletKordinatlari[0][1]-1]; // 2. hayalet i�in yukardakini kaydet
						map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]]=hayaletYan1;
						hayaletYan1=hayaletYanY;
						map[ hayaletKordinatlari[0][0]-1 ] [ hayaletKordinatlari[0][1]-1]='4'; // 2. hayaleti yukar�ya yaz
						map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]-1]='3'; // sa�a beni yaz
					}
					else if(yon2=="yukari"&& map[ hayaletKordinatlari[0][0]-1 ] [ hayaletKordinatlari[0][1]-1]=='0') // 2. hayalet yukar� ��k�yorsa ve yukarda duvar varsa
					{
						yon2="asagi";
						hayaletYanY=hayaletYan2;
						hayaletYan2=map[ hayaletKordinatlari[0][0]+1 ] [ hayaletKordinatlari[0][1]-1]; // 2. hayalet i�in a�a��dakini kaydet
						map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]]=hayaletYan1;
						hayaletYan1=hayaletYanY;
						map[ hayaletKordinatlari[0][0]+1 ] [ hayaletKordinatlari[0][1]-1]='4'; // 2. hayaleti a�a��ya yaz
						map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]-1]='3'; // sa�a beni yaz
					}
					
					else if(yon2=="asagi"&& map[ hayaletKordinatlari[0][0]+1 ] [ hayaletKordinatlari[0][1]-1]!='0') // 2. hayalet a�a�� iniyorsa ve a�a��da duvar yoksa
					{
						hayaletYanY=hayaletYan2;
						hayaletYan2=map[ hayaletKordinatlari[0][0]+1 ] [ hayaletKordinatlari[0][1]-1]; // 2. hayalet i�in yukardakini kaydet
						map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]]=hayaletYan1;
						hayaletYan1=hayaletYanY;
						map[ hayaletKordinatlari[0][0]+1 ] [ hayaletKordinatlari[0][1]-1]='4'; // 2. hayaleti yukar�ya yaz
						map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]-1]='3'; // sa�a beni yaz
					}
					else if(yon2=="asagi"&& map[ hayaletKordinatlari[0][0]+1 ] [ hayaletKordinatlari[0][1]-1]=='0') // 2. hayalet a�a�� iniyorsa ve a�a��da duvar varsa
					{
						yon2="yukari";
						hayaletYanY=hayaletYan2;
						hayaletYan2=map[ hayaletKordinatlari[0][0]-1 ] [ hayaletKordinatlari[0][1]-1]; // 2. hayalet i�in yukardakini kaydet
						map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]]=hayaletYan1;
						hayaletYan1=hayaletYanY;
						map[ hayaletKordinatlari[0][0]-1 ] [ hayaletKordinatlari[0][1]-1]='4'; // 2. hayaleti yukar�ya yaz
						map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]-1]='3'; // sa�a beni yaz
					}
					h2HareketEttiMi=true;
					h1HareketEttiMi=true;	
				}
				else
				{
					map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]]=hayaletYan1;
					hayaletYan1='4';
					map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]-1]='3'; // sa�a beni yaz
					h1HareketEttiMi=true;	
				}
				
			}
			
			else if(map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]-1]=='5') // sa��mdaki 3. hayaletse
			{
				if(h3HareketEttiMi==false )
				{
					if(yon3=="sag") // 3. hayalet sola gidiyorsa
					{
						hayaletYanY=hayaletYan3; // hayalet yan3� kaydettim
						hayaletYan3=hayaletYan1; // bulundu�um noktan�n kordinat�n� 3. hayaletin yan kordinat�na aktard�m
						hayaletYan1=hayaletYanY; 
						map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]]='5'; // bulundu�um konuma 3. hayaleti yaz
						map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]-1]='3'; // sa�a beni yaz
					}
					else if(yon3=="sol"&& map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]-2]=='0') // 2. hayalet yukar� ��k�yorsa ve yukarda duvar varsa
					{
						yon3="sag";
						hayaletYanY=hayaletYan3; // hayalet yan3� kaydettim
						hayaletYan3=hayaletYan1; // bulundu�um noktan�n kordinat�n� 3. hayaletin yan kordinat�na aktard�m
						hayaletYan1=hayaletYanY; 
						map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]]='5'; // bulundu�um konuma 3. hayaleti yaz
						map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]-1]='3'; // sa�a beni yaz
					}
				
					else if(yon3=="sol"&& map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]-2]!='0') // 2. hayalet a�a�� iniyorsa ve a�a��da duvar yoksa
					{
						hayaletYan1=hayaletYan3;
						hayaletYan3=map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]-2]; // 2. hayalet i�in yukardakini kaydet
						map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]-2]='5'; // 2. hayaleti yukar�ya yaz
						map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]-1]='3'; // sa�a beni yaz
					}
					h1HareketEttiMi=true;	
					h3HareketEttiMi=true;	
						
				}
				else //sa��mdaki 3. hayaletse ve haraket etmi�se
				{
					map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]]=hayaletYan1;
					hayaletYan1='5';
					map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]-1]='3'; // sa�a beni yaz
					h1HareketEttiMi=true;	
				}		
				
			}
			
			
			else // sa�da duvar yoksa ve sa��mdaki hayalet de�ilse
			{
				map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]]=hayaletYan1; // yerime �ncekini yaz
				hayaletYan1=map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]-1]; // sa�dakini kaydet
				map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]-1]='3'; // sa�a beni yaz
				h1HareketEttiMi=true;
			}
			
		}
			
	
		
		else if(h1HareketEttiMi==false && yon1=="sol" && map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]-1]=='0') // y�n�m sol ise solda duvar varsa 
		{
			yon1="sag";
			goto SAG1;
		}
		// 1. HAYALET SOL KONTROL� END	
	}
		
	// 1. HAYALET ���N SA� SOL KONTROL� END
		
		
	// 2. HAYALET ���N YUKARI A�A�I KONTROL� START
	if(bekleyenHayaletler[1][0]==0)
	{	// 2. HAYALET ���N YUKARI KONTROL� START
		YUKARI:
		if(h2HareketEttiMi==false && yon2=="yukari" && map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]]!='0') // yukarda duvar yoksa
		{
			if(map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]]=='3') // yukar�mdaki 1. hayaletse
			{
				if(h1HareketEttiMi==false)
				{
					if(yon1=="sag"&& map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]+1]!='0') // 1. hayalet sa�a ve sa�da duvar yoksa
					{
						hayaletYanY=hayaletYan1;
						hayaletYan1=map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]+1]; // 1. hayalet i�in sa�dakini kaydet
						map[ hayaletKordinatlari[1][0] ] [ hayaletKordinatlari[1][1]]=hayaletYan2;
						hayaletYan2=hayaletYanY;
						map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]+1]='3'; // 1. hayaleti sa�a yaz
						map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]]='4'; // yukar�ya beni yaz
					}
					else if(yon1=="sag"&& map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]+1]=='0') // 2. hayalet yukar� ��k�yorsa ve yukarda duvar varsa
					{
						yon1="sol";
						hayaletYanY=hayaletYan1;
						hayaletYan1=map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]-1]; // 2. hayalet i�in a�a��dakini kaydet
						map[ hayaletKordinatlari[1][0] ] [ hayaletKordinatlari[1][1]]=hayaletYan2;
						hayaletYan2=hayaletYanY;
						map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]-1]='3'; // 2. hayaleti a�a��ya yaz
						map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]]='4'; // sa�a beni yaz
					}
				
					else if(yon1=="sol"&& map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]-1]!='0') // 1. hayalet sa�a ve sa�da duvar yoksa
					{
						hayaletYanY=hayaletYan1;
						hayaletYan1=map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]-1]; // 1. hayalet i�in sa�dakini kaydet
						map[ hayaletKordinatlari[1][0] ] [ hayaletKordinatlari[1][1]]=hayaletYan2;
						hayaletYan2=hayaletYanY;
						map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]-1]='3'; // 1. hayaleti sa�a yaz
						map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]]='4'; // yukar�ya beni yaz
					}
					else if(yon1=="sol"&& map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]-1]=='0') // 2. hayalet yukar� ��k�yorsa ve yukarda duvar varsa
					{
						yon1="sag";
						hayaletYanY=hayaletYan1;
						hayaletYan1=map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]+1]; // 2. hayalet i�in a�a��dakini kaydet
						map[ hayaletKordinatlari[1][0] ] [ hayaletKordinatlari[1][1]]=hayaletYan2;
						hayaletYan2=hayaletYanY;
						map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]+1]='3'; // 2. hayaleti a�a��ya yaz
						map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]]='4'; // sa�a beni yaz
					}
					h1HareketEttiMi=true;
					h2HareketEttiMi=true;
				}
				
				else
				{
					map[ hayaletKordinatlari[1][0] ] [ hayaletKordinatlari[1][1]]=hayaletYan2;
					hayaletYan2='3';
					map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]]='4'; // sa�a beni yaz
					h2HareketEttiMi=true;	
				}
				
			}
			
			
			else if(map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]]=='5') // yukar�mdaki 1. hayaletse
			{
				if(h3HareketEttiMi==false)
				{
					if(yon3=="sag"&& map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]+1]!='0') // 1. hayalet sa�a ve sa�da duvar yoksa
					{
						hayaletYanY=hayaletYan3;
						hayaletYan3=map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]+1]; // 1. hayalet i�in sa�dakini kaydet
						map[ hayaletKordinatlari[1][0] ] [ hayaletKordinatlari[1][1]]=hayaletYan2;
						hayaletYan2=hayaletYanY;
						map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]+1]='5'; // 1. hayaleti sa�a yaz
						map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]]='4'; // yukar�ya beni yaz
					}
					else if(yon3=="sag"&& map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]+1]=='0') // 2. hayalet yukar� ��k�yorsa ve yukarda duvar varsa
					{
						yon3="sol";
						hayaletYanY=hayaletYan3;
						hayaletYan3=map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]-1]; // 2. hayalet i�in a�a��dakini kaydet
						map[ hayaletKordinatlari[1][0] ] [ hayaletKordinatlari[1][1]]=hayaletYan2;
						hayaletYan2=hayaletYanY;
						map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]-1]='5'; // 2. hayaleti a�a��ya yaz
						map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]]='4'; // sa�a beni yaz
					}
				
					else if(yon3=="sol"&& map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]-1]!='0') // 1. hayalet sa�a ve sa�da duvar yoksa
					{
						hayaletYanY=hayaletYan3;
						hayaletYan3=map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]-1]; // 1. hayalet i�in sa�dakini kaydet
						map[ hayaletKordinatlari[1][0] ] [ hayaletKordinatlari[1][1]]=hayaletYan2;
						hayaletYan2=hayaletYanY;
						map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]-1]='5'; // 1. hayaleti sa�a yaz
						map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]]='4'; // yukar�ya beni yaz
					}
					else if(yon3=="sol"&& map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]+1]=='0') // 2. hayalet yukar� ��k�yorsa ve yukarda duvar varsa
					{
						yon3="sag";
						hayaletYanY=hayaletYan3;
						hayaletYan3=map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]+1]; // 2. hayalet i�in a�a��dakini kaydet
						map[ hayaletKordinatlari[1][0] ] [ hayaletKordinatlari[1][1]]=hayaletYan2;
						hayaletYan2=hayaletYanY;
						map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]+1]='5'; // 2. hayaleti a�a��ya yaz
						map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]]='4'; // sa�a beni yaz
					}
					h3HareketEttiMi=true;
					h2HareketEttiMi=true;
				}
				else
				{
					map[ hayaletKordinatlari[1][0] ] [ hayaletKordinatlari[1][1]]=hayaletYan2;
					hayaletYan2='5';
					map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]]='4'; // sa�a beni yaz
					h2HareketEttiMi=true;	
				}
			}
				
			else // sa�da duvar yoksa ve sa��mdaki hayalet de�ilse
			{
				map[ hayaletKordinatlari[1][0] ] [ hayaletKordinatlari[1][1]]=hayaletYan2; // yerime �ncekini yaz
				hayaletYan2=map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]]; // sa�dakini kaydet
				map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]]='4'; // sa�a beni yaz
				h2HareketEttiMi=true;
			}		
		}
		
		else if(h2HareketEttiMi==false && yon2=="yukari" && map[ hayaletKordinatlari[1][0]-1 ] [ hayaletKordinatlari[1][1]]=='0') // y�n�m sa� ise sa�da duvar varsa 
		{
			yon2="asagi";
			goto ASAGI;
		}
		// 2. HAYALET ���N YUKARI KONTROL� END
		
		ASAGI:
		if(h2HareketEttiMi==false && yon2=="asagi" && map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]]!='0') // yukarda duvar yoksa
		{
			if( map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]]=='3') // yukar�mdaki 1. hayaletse
			{
				if(h1HareketEttiMi==false)
				{
					if(yon1=="sag"&& map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]+1]!='0') // 1. hayalet sa�a ve sa�da duvar yoksa
					{
						hayaletYanY=hayaletYan1;
						hayaletYan1=map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]+1]; // 1. hayalet i�in sa�dakini kaydet
						map[ hayaletKordinatlari[1][0] ] [ hayaletKordinatlari[1][1]]=hayaletYan2;
						hayaletYan2=hayaletYanY;
						map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]+1]='3'; // 1. hayaleti sa�a yaz
						map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]]='4'; // yukar�ya beni yaz
					}
					else if(yon1=="sag"&& map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]+1]=='0') // 2. hayalet yukar� ��k�yorsa ve yukarda duvar varsa
					{
						yon1="sol";
						hayaletYanY=hayaletYan1;
						hayaletYan1=map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]-1]; // 2. hayalet i�in a�a��dakini kaydet
						map[ hayaletKordinatlari[1][0] ] [ hayaletKordinatlari[1][1]]=hayaletYan2;
						hayaletYan2=hayaletYanY;
						map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]-1]='3'; // 2. hayaleti a�a��ya yaz
						map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]]='4'; // sa�a beni yaz
					}
					
					else if(yon1=="sol"&& map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]-1]!='0') // 1. hayalet sa�a ve sa�da duvar yoksa
					{
						hayaletYanY=hayaletYan1;
						hayaletYan1=map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]-1]; // 1. hayalet i�in sa�dakini kaydet
						map[ hayaletKordinatlari[1][0] ] [ hayaletKordinatlari[1][1]]=hayaletYan2;
						hayaletYan2=hayaletYanY;
						map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]-1]='3'; // 1. hayaleti sa�a yaz
						map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]]='4'; // yukar�ya beni yaz
					}
					else if(yon1=="sol"&& map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]-1]=='0') // 2. hayalet yukar� ��k�yorsa ve yukarda duvar varsa
					{
						yon1="sag";
						hayaletYanY=hayaletYan1;
						hayaletYan1=map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]+1]; // 2. hayalet i�in a�a��dakini kaydet
						map[ hayaletKordinatlari[1][0] ] [ hayaletKordinatlari[1][1]]=hayaletYan2;
						hayaletYan2=hayaletYanY;
						map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]+1]='3'; // 2. hayaleti a�a��ya yaz
						map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]]='4'; // sa�a beni yaz
					}
					h1HareketEttiMi=true;
					h2HareketEttiMi=true;	
				}
				else
				{
					map[ hayaletKordinatlari[1][0] ] [ hayaletKordinatlari[1][1]]=hayaletYan2;
					hayaletYan2='3';
					map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]]='4'; // sa�a beni yaz
					h2HareketEttiMi=true;	
				}
				
			}
			
			
			else if(map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]]=='5') // yukar�mdaki 1. hayaletse
			{
				if(h3HareketEttiMi==false)
				{
					if(yon3=="sag"&& map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]+1]!='0') // 1. hayalet sa�a ve sa�da duvar yoksa
					{
						hayaletYanY=hayaletYan3;
						hayaletYan3=map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]+1]; // 1. hayalet i�in sa�dakini kaydet
						map[ hayaletKordinatlari[1][0] ] [ hayaletKordinatlari[1][1]]=hayaletYan2;
						hayaletYan2=hayaletYanY;
						map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]+1]='5'; // 1. hayaleti sa�a yaz
						map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]]='4'; // yukar�ya beni yaz
					}
					else if(yon3=="sag"&& map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]+1]=='0') // 2. hayalet yukar� ��k�yorsa ve yukarda duvar varsa
					{
						yon3="sol";
						hayaletYanY=hayaletYan3;
						hayaletYan3=map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]-1]; // 2. hayalet i�in a�a��dakini kaydet
						map[ hayaletKordinatlari[1][0] ] [ hayaletKordinatlari[1][1]]=hayaletYan2;
						hayaletYan2=hayaletYanY;
						map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]-1]='5'; // 2. hayaleti a�a��ya yaz
						map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]]='4'; // sa�a beni yaz
					}
				
					else if(yon3=="sol"&& map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]-1]!='0') // 1. hayalet sa�a ve sa�da duvar yoksa
					{
						hayaletYanY=hayaletYan3;
						hayaletYan3=map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]-1]; // 1. hayalet i�in sa�dakini kaydet
						map[ hayaletKordinatlari[1][0] ] [ hayaletKordinatlari[1][1]]=hayaletYan2;
						hayaletYan2=hayaletYanY;
						map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]-1]='5'; // 1. hayaleti sa�a yaz
						map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]]='4'; // yukar�ya beni yaz
					}
					else if(yon3=="sol"&& map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]+1]=='0') // 2. hayalet yukar� ��k�yorsa ve yukarda duvar varsa
					{
						yon3="sag";
						hayaletYanY=hayaletYan3;
						hayaletYan3=map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]+1]; // 2. hayalet i�in a�a��dakini kaydet
						map[ hayaletKordinatlari[1][0] ] [ hayaletKordinatlari[1][1]]=hayaletYan2;
						hayaletYan2=hayaletYanY;
						map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]+1]='5'; // 2. hayaleti a�a��ya yaz
						map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]]='4'; // sa�a beni yaz
					}
					h3HareketEttiMi=true;
					h2HareketEttiMi=true;
				}
				else
				{
					map[ hayaletKordinatlari[1][0] ] [ hayaletKordinatlari[1][1]]=hayaletYan2;
					hayaletYan2='5';
					map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]]='4'; // sa�a beni yaz
					h2HareketEttiMi=true;	
				}
				
			}
				
			else // sa�da duvar yoksa ve sa��mdaki hayalet de�ilse
			{
				map[ hayaletKordinatlari[1][0] ] [ hayaletKordinatlari[1][1]]=hayaletYan2; // yerime �ncekini yaz
				hayaletYan2=map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]]; // sa�dakini kaydet
				map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]]='4'; // sa�a beni yaz
				h2HareketEttiMi=true;
			}		
		}
		
		else if(h2HareketEttiMi==false && yon2=="asagi" && map[ hayaletKordinatlari[1][0]+1 ] [ hayaletKordinatlari[1][1]]=='0') // y�n�m sa� ise sa�da duvar varsa 
		{
			yon2="yukari";
			goto YUKARI;
		}
	}
		
	// 2. HAYALET ���N A�A�I KONTROL END
		
		// 2. HAYALET ���N YUKARI A�A�I KONTROL END
		
				//BURADA KALDIM G�NCELLEMELERE DEVAM
		
		//3. HAYALET ���N SA� SOL KONTROL� START	
		
	if(bekleyenHayaletler[2][0]==0)
	{
		//3. HAYALET ���N SA� KONTROL� START	
		SAG3:
		if(h3HareketEttiMi==false && yon3=="sag" && map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]+1]!='0') // sa�da duvar yoksa
		{
			if(map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]+1]=='4') // sa��mdaki 2. hayaletse
			{
				if(h2HareketEttiMi==false)
				{
					if(yon2=="yukari"&& map[ hayaletKordinatlari[2][0]-1 ] [ hayaletKordinatlari[2][1]+1]!='0') // 2. hayalet yukar� ��k�yorsa ve yukarda duvar yoksa
					{
						hayaletYanY=hayaletYan2;
						hayaletYan2=map[ hayaletKordinatlari[2][0]-1 ] [ hayaletKordinatlari[2][1]+1]; // 2. hayalet i�in yukardakini kaydet
						map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]]=hayaletYan1;
						hayaletYan3=hayaletYanY;
						map[ hayaletKordinatlari[2][0]-1 ] [ hayaletKordinatlari[2][1]+1]='4'; // 2. hayaleti yukar�ya yaz
						map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]+1]='5'; // sa�a beni yaz
					}
					else if(yon2=="yukari"&& map[ hayaletKordinatlari[2][0]-1 ] [ hayaletKordinatlari[2][1]+1]=='0') // 2. hayalet yukar� ��k�yorsa ve yukarda duvar varsa
					{
						yon2="asagi";
						hayaletYanY=hayaletYan2;
						hayaletYan2=map[ hayaletKordinatlari[2][0]+1 ] [ hayaletKordinatlari[2][1]+1]; // 2. hayalet i�in a�a��dakini kaydet
						map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]]=hayaletYan1;
						hayaletYan3=hayaletYanY;
						map[ hayaletKordinatlari[2][0]+1 ] [ hayaletKordinatlari[2][1]+1]='4'; // 2. hayaleti a�a��ya yaz
						map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]+1]='5'; // sa�a beni yaz
					}
					
					else if(yon2=="asagi"&& map[ hayaletKordinatlari[2][0]+1 ] [ hayaletKordinatlari[2][1]+1]!='0') // 2. hayalet a�a�� iniyorsa ve a�a��da duvar yoksa
					{
						hayaletYanY=hayaletYan2;
						hayaletYan2=map[ hayaletKordinatlari[2][0]+1 ] [ hayaletKordinatlari[2][1]+1]; // 2. hayalet i�in yukardakini kaydet
						map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]]=hayaletYan1;
						hayaletYan3=hayaletYanY;
						map[ hayaletKordinatlari[2][0]+1 ] [ hayaletKordinatlari[2][1]+1]='4'; // 2. hayaleti yukar�ya yaz
						map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]+1]='5'; // sa�a beni yaz
					}
					else if(yon2=="asagi"&& map[ hayaletKordinatlari[2][0]+1 ] [ hayaletKordinatlari[2][1]+1]=='0') // 2. hayalet a�a�� iniyorsa ve a�a��da duvar varsa
					{
						yon2="yukari";
						hayaletYanY=hayaletYan2;
						hayaletYan2=map[ hayaletKordinatlari[2][0]-1 ] [ hayaletKordinatlari[2][1]+1]; // 2. hayalet i�in yukardakini kaydet
						map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]]=hayaletYan1;
						hayaletYan3=hayaletYanY;
						map[ hayaletKordinatlari[2][0]-1 ] [ hayaletKordinatlari[2][1]+1]='4'; // 2. hayaleti yukar�ya yaz
						map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]+1]='5'; // sa�a beni yaz
					}	
					h2HareketEttiMi=true;
					h3HareketEttiMi=true;
				}
				else
				{
					map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]]=hayaletYan3;
					hayaletYan3='4';
					map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]+1]='5'; // sa�a beni yaz
					h3HareketEttiMi=true;	
				}
				
			}
			
			else if(map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]+1]=='3') // sa��mdaki 3. hayaletse
			{
				if(h1HareketEttiMi==false )
				{
					if(yon1=="sol") // 3. hayalet sola gidiyorsa
					{
						hayaletYanY=hayaletYan1; // hayalet yan3� kaydettim
						hayaletYan1=hayaletYan3; // bulundu�um noktan�n kordinat�n� 3. hayaletin yan kordinat�na aktard�m
						hayaletYan3=hayaletYanY; 
						map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]]='3'; // bulundu�um konuma 3. hayaleti yaz
						map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]+1]='5'; // sa�a beni yaz
					}
					else if(yon1=="sag"&& map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]+2]=='0') // 2. hayalet yukar� ��k�yorsa ve yukarda duvar varsa
					{
						yon1="sol";
						hayaletYanY=hayaletYan1; // hayalet yan3� kaydettim
						hayaletYan1=hayaletYan3; // bulundu�um noktan�n kordinat�n� 3. hayaletin yan kordinat�na aktard�m
						hayaletYan3=hayaletYanY; 
						map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]]='3'; // bulundu�um konuma 3. hayaleti yaz
						map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]+1]='5'; // sa�a beni yaz
					}
				
					else if(yon1=="sag"&& map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]+2]!='0') // 2. hayalet a�a�� iniyorsa ve a�a��da duvar yoksa
					{
						hayaletYan3=hayaletYan1;
						hayaletYan1=map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]+2]; // 2. hayalet i�in yukardakini kaydet
						map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]+2]='3'; // 2. hayaleti yukar�ya yaz
						map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]+1]='5'; // sa�a beni yaz
					}
					h3HareketEttiMi=true;	
					h1HareketEttiMi=true;	
						
				}
				else //sa��mdaki 3. hayaletse ve haraket etmemi�se
				{
					map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]]=hayaletYan3;
					hayaletYan3='3';
					map[ hayaletKordinatlari[0][0] ] [ hayaletKordinatlari[0][1]+1]='5'; // sa�a beni yaz
					h3HareketEttiMi=true;	
				}		
				
			}
			
			else // sa�da duvar yoksa ve sa��mdaki hayalet de�ilse
			{
				map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]]=hayaletYan3; // yerime �ncekini yaz
				hayaletYan3=map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]+1]; // sa�dakini kaydet
				map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]+1]='5'; // sa�a beni yaz
				h3HareketEttiMi=true;
			}
			
		}
		
		else if(h3HareketEttiMi==false && yon3=="sag" && map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]+1]=='0') // y�n�m sa� ise sa�da duvar varsa 
		{
			yon3="sol";
			goto SOL3;
		}
		
	
		SOL3:
		if(h3HareketEttiMi==false && yon3=="sol" && map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]-1]!='0') // sa�da duvar yoksa
		{
			if(h2HareketEttiMi==false && map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]-1]=='4') // sa��mdaki 2. hayaletse
			{
				if(yon2=="yukari"&& map[ hayaletKordinatlari[2][0]-1 ] [ hayaletKordinatlari[2][1]-1]!='0') // 2. hayalet yukar� ��k�yorsa ve yukarda duvar yoksa
				{
					hayaletYanY=hayaletYan2;
					hayaletYan2=map[ hayaletKordinatlari[2][0]-1 ] [ hayaletKordinatlari[2][1]-1]; // 2. hayalet i�in yukardakini kaydet
					map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]]=hayaletYan3;
					hayaletYan3=hayaletYanY;
					map[ hayaletKordinatlari[2][0]-1 ] [ hayaletKordinatlari[2][1]-1]='4'; // 2. hayaleti yukar�ya yaz
					map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]-1]='5'; // sa�a beni yaz
				}
				else if(yon2=="yukari"&& map[ hayaletKordinatlari[2][0]-1 ] [ hayaletKordinatlari[2][1]-1]=='0') // 2. hayalet yukar� ��k�yorsa ve yukarda duvar varsa
				{
					
					yon2="asagi";
					hayaletYanY=hayaletYan2;
					hayaletYan2=map[ hayaletKordinatlari[2][0]+1 ] [ hayaletKordinatlari[2][1]-1]; // 2. hayalet i�in a�a��dakini kaydet
					map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]]=hayaletYan3;
					hayaletYan3=hayaletYanY;
					map[ hayaletKordinatlari[2][0]+1 ] [ hayaletKordinatlari[2][1]-1]='4'; // 2. hayaleti a�a��ya yaz
					map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]-1]='5'; // sa�a beni yaz
				}
				
				else if(yon2=="asagi"&& map[ hayaletKordinatlari[2][0]+1 ] [ hayaletKordinatlari[2][1]-1]!='0') // 2. hayalet a�a�� iniyorsa ve a�a��da duvar yoksa
				{
					hayaletYanY=hayaletYan2;
					hayaletYan2=map[ hayaletKordinatlari[2][0]+1 ] [ hayaletKordinatlari[2][1]-1]; // 2. hayalet i�in yukardakini kaydet
					map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]]=hayaletYan3;
					hayaletYan3=hayaletYanY;
					map[ hayaletKordinatlari[2][0]+1 ] [ hayaletKordinatlari[2][1]-1]='4'; // 2. hayaleti yukar�ya yaz
					map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]-1]='5'; // sa�a beni yaz
				}
				else if(yon2=="asagi"&& map[ hayaletKordinatlari[2][0]+1 ] [ hayaletKordinatlari[2][1]-1]=='0') // 2. hayalet a�a�� iniyorsa ve a�a��da duvar varsa
				{
					yon2="yukari";
					hayaletYanY=hayaletYan2;
					hayaletYan2=map[ hayaletKordinatlari[2][0]-1 ] [ hayaletKordinatlari[2][1]-1]; // 2. hayalet i�in yukardakini kaydet
					map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]]=hayaletYan3;
					hayaletYan3=hayaletYanY;
					map[ hayaletKordinatlari[2][0]-1 ] [ hayaletKordinatlari[2][1]-1]='4'; // 2. hayaleti yukar�ya yaz
					map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]-1]='5'; // sa�a beni yaz
				}	
				h2HareketEttiMi=true;
				h3HareketEttiMi=true;
			}
			
			
			else if(map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]-1]=='3') // sa��mdaki 3. hayaletse
			{
				if(h1HareketEttiMi==false )
				{
					if(yon1=="sag") // 3. hayalet sola gidiyorsa
					{
						hayaletYanY=hayaletYan1; // hayalet yan3� kaydettim
						hayaletYan1=hayaletYan3; // bulundu�um noktan�n kordinat�n� 3. hayaletin yan kordinat�na aktard�m
						hayaletYan3=hayaletYanY; 
						map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]]='3'; // bulundu�um konuma 3. hayaleti yaz
						map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]-1]='5'; // sa�a beni yaz
					}
					else if(yon1=="sol"&& map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]-2]=='0') // 2. hayalet yukar� ��k�yorsa ve yukarda duvar varsa
					{
						yon1="sag";
						hayaletYanY=hayaletYan1; // hayalet yan3� kaydettim
						hayaletYan1=hayaletYan3; // bulundu�um noktan�n kordinat�n� 3. hayaletin yan kordinat�na aktard�m
						hayaletYan3=hayaletYanY; 
						map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]]='3'; // bulundu�um konuma 3. hayaleti yaz
						map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]-1]='5'; // sa�a beni yaz
					}
				
					else if(yon1=="sol"&& map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]-2]!='0') // 2. hayalet a�a�� iniyorsa ve a�a��da duvar yoksa
					{
						hayaletYan3=hayaletYan1;
						hayaletYan1=map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]-2]; // 2. hayalet i�in yukardakini kaydet
						map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]-2]='3'; // 2. hayaleti yukar�ya yaz
						map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]-1]='5'; // sa�a beni yaz
					}
					h3HareketEttiMi=true;	
					h1HareketEttiMi=true;	
						
				}
				else //sa��mdaki 3. hayaletse ve haraket etmi�se
				{
					map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]]=hayaletYan3;
					hayaletYan3='3';
					map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]-1]='5'; // sa�a beni yaz
					h3HareketEttiMi=true;	
				}		
				
			}
			
			
			else // sa�da duvar yoksa ve sa��mdaki hayalet de�ilse
			{
				map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]]=hayaletYan3; // yerime �ncekini yaz
				hayaletYan3=map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]-1]; // sa�dakini kaydet
				map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]-1]='5'; // sa�a beni yaz
				h3HareketEttiMi=true;
			}
			
			
		}
		
		else if(h3HareketEttiMi==false && yon3=="sol" && map[ hayaletKordinatlari[2][0] ] [ hayaletKordinatlari[2][1]-1]=='0') // y�n�m sol ise solda duvar varsa 
		{
			yon3="sag";
			goto SAG3;
		}	
	}
		
		h1HareketEttiMi=false;
		h2HareketEttiMi=false;
		h3HareketEttiMi=false;
	
}


void diskTopla(Queue<int>& meyveQKordinatlari) 
{
	meyveSayisi=meyveSayisiBul();
	int meyveKordinatlari[meyveSayisi][2];
	int hayaletKordinatlari[hayaletSayisi][2];
//	int pacmanKordinat[1][2];
	
	mapYazdir(hayaletKordinatlari,meyveKordinatlari,pacmanKordinat); // map �zerinden bak�yor // mapyazdir
	hayaletHareket(hayaletKordinatlari);
	
	if(pacmanHayaletUstunde==true) // pacman daha �nce bir hayalet ile ayn� konumda olmu�sa
	{ 
		
		pacmanKordinat[0][0]=pacmanHayaletUstundeKord[0][0];
		pacmanKordinat[0][1]=pacmanHayaletUstundeKord[0][1];
		map[ pacmanHayaletUstundeKord[0][0]] [pacmanHayaletUstundeKord[0][1]]  ='9';
		pacmanHayaletUstunde=false;
	}
	
	//YUKARI KONTROL� START
	if(map[ pacmanKordinat[0][0]-1 ] [ pacmanKordinat[0][1] ] != '0' && map[ pacmanKordinat[0][0]-1 ] [ pacmanKordinat[0][1] ] != ' ' ) // yukar� 0 de�ilse
	{
		
		if(map[ pacmanKordinat[0][0]-1 ] [ pacmanKordinat[0][1] ] == '1') //yukar� 1 ise
		{
			map[ pacmanKordinat[0][0]-1 ] [ pacmanKordinat[0][1] ] = '9'; // yukar�y� 9 yap
			if(meyveYedinMi==true)
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = '1';
				meyveYedinMi=false;
			}
			else
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = ' '; // eski konumu d yap
			}
			meyveOlustur(meyveQKordinatlari); // disk sayma ve meyve olu�turma mevzusu
			diskSayisi--;
			sureHesapla('N'); // s�re azaltt�k
		}
		else if(map[ pacmanKordinat[0][0]-1 ] [ pacmanKordinat[0][1] ] == '2') // yukar� 2 ise
		{
			hayaletBeklet(hayaletKordinatlari);
			//meyveSayisi-- yap�labilir
			meyveQKordinatlari.enqueue(pacmanKordinat[0][0]-1); // meyvenin i kordinat�n� kuyru�a ekledik
			meyveQKordinatlari.enqueue(pacmanKordinat[0][1]);  // meyvenin j kordinat�n� ekledik
			 
			map[ pacmanKordinat[0][0]-1 ] [ pacmanKordinat[0][1] ] = '9';
			
			if(meyveYedinMi==true) //t�m kodlarda olacak
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = '1';
				meyveYedinMi=false;
			}
			else
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = ' '; // eski konumu d yap
			}
			meyveYedinMi=true;
			diskSayilsinMi=true;
			sureHesapla('M'); // s�re art�rd�k
			
			
		}
		else if(map[ pacmanKordinat[0][0]-1 ] [ pacmanKordinat[0][1] ] != ' ') // yukar� d de�ilse, ozaman hayaletlerden biridir 
		{
			
			pacmanHayaletUstundeKord[0][0]=pacmanKordinat[0][0]-1;
			pacmanHayaletUstundeKord[0][1]=pacmanKordinat[0][1];
			pacmanHayaletUstunde=true;
			if(meyveYedinMi==true)
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = '1';
				meyveYedinMi=false;
			}
			else
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = ' ';
			}
			sureHesapla('H'); // s�re azaltt�k
		}
	}
	
	//YUKARI KONTROL� END
	
	//SA� KONTROL� START
	
	else if(map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1]+1 ] != '0' && map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1]+1 ] != ' ') // yukar� 0 de�ilse
	{
		
		if(map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1]+1 ] == '1') //yukar� 1 ise
		{
			map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1]+1 ] = '9'; // yukar�y� 9 yap
			if(meyveYedinMi==true)
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = '1';
				meyveYedinMi=false;
			}
			else
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = ' '; // eski konumu d yap
			}
			meyveOlustur(meyveQKordinatlari);
			diskSayisi--;
			sureHesapla('N'); // s�re azaltt�k
		}
		else if(map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1]+1 ] == '2') // yukar� 2 ise
		{
			meyveQKordinatlari.enqueue(pacmanKordinat[0][0]); // meyvenin i kordinat�n� kuyru�a ekledik
			meyveQKordinatlari.enqueue(pacmanKordinat[0][1]+1);  // meyvenin j kordinat�n� ekledik
			 
			map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1]+1 ] = '9';
			
			if(meyveYedinMi==true) //t�m kodlarda olacak
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = '1';
				meyveYedinMi=false;
			}
			else
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = ' '; // eski konumu d yap
			}
			meyveYedinMi=true;
			diskSayilsinMi=true;
			sureHesapla('M'); // s�re art�rd�k
			
		}
		else if(map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1]+1 ] != ' ') // yukar� d de�ilse, ozaman hayaletlerden biridir 
		{
			
			pacmanHayaletUstundeKord[0][0]=pacmanKordinat[0][0];
			pacmanHayaletUstundeKord[0][1]=pacmanKordinat[0][1]+1;
			pacmanHayaletUstunde=true;
			if(meyveYedinMi==true)
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = '1';
				meyveYedinMi=false;
			}
			else
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = ' ';
			}
			sureHesapla('H'); // s�re azaltt�k
		}
	}
	
	//SA� KONTROL� END
	
	//A�A�I KONTROL� START
	
	
	else if(map[ pacmanKordinat[0][0]+1 ] [ pacmanKordinat[0][1] ] != '0' && map[ pacmanKordinat[0][0]+1 ] [ pacmanKordinat[0][1] ] != ' ') // yukar� 0 de�ilse
	{
		
		if(map[ pacmanKordinat[0][0]+1 ] [ pacmanKordinat[0][1] ] == '1') //yukar� 1 ise
		{
			map[ pacmanKordinat[0][0]+1 ] [ pacmanKordinat[0][1] ] = '9'; // yukar�y� 9 yap
			if(meyveYedinMi==true)
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = '1';
				meyveYedinMi=false;
			}
			else
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = ' '; // eski konumu d yap
			}
			meyveOlustur(meyveQKordinatlari);
			diskSayisi--;
			sureHesapla('N'); // s�re azaltt�k
		}
		else if(map[ pacmanKordinat[0][0]+1 ] [ pacmanKordinat[0][1] ] == '2') // yukar� 2 ise
		{
			meyveQKordinatlari.enqueue(pacmanKordinat[0][0]+1); // meyvenin i kordinat�n� kuyru�a ekledik
			meyveQKordinatlari.enqueue(pacmanKordinat[0][1]);  // meyvenin j kordinat�n� ekledik
			 
			map[ pacmanKordinat[0][0]+1 ] [ pacmanKordinat[0][1] ] = '9';
			
			if(meyveYedinMi==true) //t�m kodlarda olacak
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = '1';
				meyveYedinMi=false;
			}
			else
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = ' '; // eski konumu d yap
			}
			meyveYedinMi=true;
			diskSayilsinMi=true;
			sureHesapla('M'); // s�re art�rd�k
			
		}
		else if(map[ pacmanKordinat[0][0]+1 ] [ pacmanKordinat[0][1] ] != ' ') // yukar� d de�ilse, ozaman hayaletlerden biridir 
		{
			
			pacmanHayaletUstundeKord[0][0]=pacmanKordinat[0][0]+1;
			pacmanHayaletUstundeKord[0][1]=pacmanKordinat[0][1];
			pacmanHayaletUstunde=true;
			if(meyveYedinMi==true)
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = '1';
				meyveYedinMi=false;
			}
			else
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = ' ';
			}
			sureHesapla('H'); // s�re azaltt�k
		}
	}
	
	//A�A�I KONTROL� END
	
	//SOL KONTROL� START
	
	else if(map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1]-1 ] != '0' && map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1]-1 ] != ' ') // yukar� 0 de�ilse
	{
		
		if(map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1]-1 ] == '1') //yukar� 1 ise
		{
			map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1]-1 ] = '9'; // yukar�y� 9 yap
			if(meyveYedinMi==true)
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = '1';
				meyveYedinMi=false;
			}
			else
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = ' '; // eski konumu d yap
			}
			meyveOlustur(meyveQKordinatlari);
			diskSayisi--;
			sureHesapla('N'); // s�re azaltt�k
		}
		else if(map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1]-1 ] == '2') // yukar� 2 ise
		{
			meyveQKordinatlari.enqueue(pacmanKordinat[0][0]); // meyvenin i kordinat�n� kuyru�a ekledik
			meyveQKordinatlari.enqueue(pacmanKordinat[0][1]-1);  // meyvenin j kordinat�n� ekledik
			 
			map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1]-1 ] = '9';
			
			if(meyveYedinMi==true) //t�m kodlarda olacak
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = '1';
				meyveYedinMi=false;
			}
			else
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = ' '; // eski konumu d yap
			}
			meyveYedinMi=true;
			diskSayilsinMi=true;
			sureHesapla('M'); // s�re art�rd�k
			
		}
		else if(map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1]-1 ] != ' ') // yukar� d de�ilse, ozaman hayaletlerden biridir 
		{
			
			pacmanHayaletUstundeKord[0][0]=pacmanKordinat[0][0];
			pacmanHayaletUstundeKord[0][1]=pacmanKordinat[0][1]-1;
			pacmanHayaletUstunde=true;
			if(meyveYedinMi==true)
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = '1';
				meyveYedinMi=false;
			}
			else
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = ' ';
			}
			sureHesapla('H'); // s�re azaltt�k
		}
	}
	
	//SOL KONTROL� END
	
	
	else // etraf�m�zda 1,2 ya da hayalet yoksa d var m� diye kontrol edicez
	{
		
		if(map[ pacmanKordinat[0][0]-1 ] [ pacmanKordinat[0][1] ] == ' ') // yukar� d ise
		{
			map[ pacmanKordinat[0][0]-1 ] [ pacmanKordinat[0][1] ] = '9'; 
			if(meyveYedinMi==true)
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = '1';
				meyveYedinMi=false;
			}
			else
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = ' '; // eski konumu d yap
			}
			sureHesapla('N'); // s�re azaltt�k
		}
		else if(map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1]+1 ] == ' ') // yukar� d ise
		{
			map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1]+1 ] = '9'; 
			if(meyveYedinMi==true)
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = '1';
				meyveYedinMi=false;
			}
			else
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = ' '; // eski konumu d yap
			}
			sureHesapla('N'); // s�re azaltt�k
		}
		else if(map[ pacmanKordinat[0][0]+1 ] [ pacmanKordinat[0][1] ] == ' ') // yukar� d ise
		{
			map[ pacmanKordinat[0][0]+1 ] [ pacmanKordinat[0][1] ] = '9'; 
			if(meyveYedinMi==true)
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = '1';
				meyveYedinMi=false;
			}
			else
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = ' '; // eski konumu d yap
			}
			sureHesapla('N'); // s�re azaltt�k
		}
		else if(map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1]-1 ] == ' ') // yukar� d ise
		{
			map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1]-1 ] = '9'; 
			if(meyveYedinMi==true)
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = '1';
				meyveYedinMi=false;
			}
			else
			{
				map[ pacmanKordinat[0][0] ] [ pacmanKordinat[0][1] ] = ' '; // eski konumu d yap
			}
			sureHesapla('N'); // s�re azaltt�k
		}
	}
	
	for(int i=0;i<3;i++)
	{
		if(bekleyenHayaletler[i][0]==1) // 1. hayalet beklemedeyse
		{
			if(i==0)
			{
				h1HareketEttiMi=true;
			}
			else if(i==1)
			{
				h2HareketEttiMi=true;
			}
			else if(i==2)
			{
				h3HareketEttiMi=true;
			}
			
			bekleyenHayaletler[i][1]--; // s�resini 1 azalt
			if(bekleyenHayaletler[i][1]==0) // s�resi 0 olduysa
			{
				if(i==0)
				{
					h1HareketEttiMi=false;
				}
				else if(i==1)
				{
					h2HareketEttiMi=false;
				}
				else if(i==2)
				{
					h3HareketEttiMi=false;
				}
				bekleyenHayaletler[i][0]=0; // beklemeden ��kar
			}
		}
	}
	
	
	
	

}

#endif
