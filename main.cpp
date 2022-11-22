#include "header.h"
using namespace std;





int main() 
{
	int x,y;
	int yiyilenMeyveler[meyveSayisiBul()][2];
	ifstream dosyaKontrolm;
	dosyaKontrolm.open("meyveKonum.txt"); // dosyay� a�may� dene
 	if(dosyaKontrolm) // dosya varsa 
	{
		dosyaKontrolm.close(); // dosyadan ��k
		remove("meyveKonum.txt"); // dosyay� sil
		// dosyay� olu�turuyoruz
	
	} 
	else //dosya yoksa 
 	{
		// dosyay� olu�turuyoruz
		dosyaKontrolm.close();
		
	}

	ofstream dosyaAcm;
	dosyaAcm.open("meyveKonum.txt",ios_base::app);
 	dosyaAcm.close();
	ifstream dosyaKontrolh;
	dosyaKontrolh.open("hayaletKonum.txt"); // dosyay� a�may� dene
	
 	if(dosyaKontrolh) // dosya varsa 
	{
		dosyaKontrolh.close(); // dosyadan ��k
		remove("hayaletKonum.txt"); // dosyay� sil
		// dosyay� olu�turuyoruz
		
	} 
	else //dosya yoksa 
	{
		dosyaKontrolh.close();
	}
	
	ofstream dosyaAch;
	dosyaAch.open("hayaletKonum.txt",ios_base::app);
 	dosyaAch.close();

	ifstream dosyaKontrolp;
	dosyaKontrolp.open("pacmanHareket.txt"); // dosyay� a�may� dene
	
 	if(dosyaKontrolp) // dosya varsa 
	{
		dosyaKontrolp.close(); // dosyadan ��k
		remove("pacmanHareket.txt"); // dosyay� sil
		
	} 
	else //dosya yoksa 
	{
		dosyaKontrolp.close();
	}
	// dosyay� olu�turuyoruz
	ofstream dosyaAcp;
	dosyaAcp.open("pacmanHareket.txt",ios_base::app);
	dosyaAcp.close();

	diskSayisiBul();
	Queue<int> meyveQKordinatlari;
	oyunAlaniOku(); // oyunalani

	while(startTime>0)
	{
		
		for(int i=0;i<haritaBoyutu();i++)
 		{
 			for(int j=0;j<haritaBoyutu();j++)
 			{
 				
 				cout<<map[i][j];
 				
 			}
 			cout<<endl;
 		}
 		
 		diskTopla(meyveQKordinatlari);
 		
 		if(meyveYedinMi==true)
 		{
 			ofstream dosyaAcm;
			dosyaAcm.open("meyveKonum.txt",ios_base::app);
 			kacMeyveYiyildi++;
 			x=meyveQKordinatlari.front();
			meyveQKordinatlari.dequeue();
			y=meyveQKordinatlari.front();
			meyveQKordinatlari.dequeue();
			meyveQKordinatlari.enqueue(x);
			meyveQKordinatlari.enqueue(y);
			
			for(int i=0;i<meyveSayisiBul();i++)
			{
				if(yiyilenMeyveler[i][0]==x && yiyilenMeyveler[i][1]==y)
				{
					kacMeyveYiyildi=i+1;
					bulundu=true;
				}
				else if(i==meyveSayisiBul()-1 && bulundu==false)
				{
					yiyilenMeyveler[kacMeyveYiyildi-1][0]=x;
					yiyilenMeyveler[kacMeyveYiyildi-1][1]=y;
				}
			}
			
 			dosyaAcm<<"Meyve"<<kacMeyveYiyildi<<"-> ("<<x<<","<<y<<")"<<endl;
 			
 			if(meyveOlustuMu==true)
 			{
 				for(int i=0;i<meyveSayisiBul();i++)
				{
					if(yiyilenMeyveler[i][0]==mX && yiyilenMeyveler[i][1]==mY)
					{
						
						dosyaAcm<<"Meyve"<<i+1<<" yeniden olu�turuldu."<<endl;
					}
					
				}
			}
 			
 			dosyaAcm.close();
 			
 			ofstream dosyaAch;
			dosyaAch.open("hayaletKonum.txt",ios_base::app);
 			dosyaAch<<"Hayalet1 bekleme durumunda"<<endl<<"Hayalet2 bekleme durumunda"<<endl<<"Hayalet3 bekleme durumunda"<<endl;
 			dosyaAch.close();
 			
		}
		
		if(hayaletGorduMu==true) // hayalet ile kar��la�t�ysam
		{
			ofstream dosyaAch;
			dosyaAch.open("hayaletKonum.txt",ios_base::app);
			
 			kacHayaletYiyildi++;
			
			
 			dosyaAch<<"Hayalet"<<kacHayaletYiyildi<<"-> ("<<pacmanHayaletUstundeKord[0][0]<<","<<pacmanHayaletUstundeKord[0][1]<<")"<<endl;
			
 			hayaletGorduMu=false;
 			dosyaAch.close();
		}
		
		ofstream dosyaAcp;
		dosyaAcp.open("pacmanHareket.txt",ios_base::app);
		dosyaAcp<<"("<<pacmanKordinat[0][0]<<","<<pacmanKordinat[0][1]<<" � "<<startTime+1<<")"<<endl;
		dosyaAcp.close();
		
 		
 		system("cls");
 		if(diskSayisi<=0)
 		{
 			ofstream dosyaAcp;
			dosyaAcp.open("pacmanHareket.txt",ios_base::app);
			dosyaAcp<<"TUM DISKLERI TOPLADIGI ICIN OYUN KAZANILDI"<<endl<<"Toplad��� disk say�s�: "<<baslangicDiskSayisi-diskSayisi<<endl<<"Hayaletle �arp��ma say�s�: "<<3-hak<<endl;;
			dosyaAcp.close();
 			cout<<"TUM DISKLERI TOPLADIGI ICIN OYUN KAZANILDI"<<endl;
 			break;		
		}
 		if(hak<=0)
 		{
 			ofstream dosyaAcp;
			dosyaAcp.open("pacmanHareket.txt",ios_base::app);
			dosyaAcp<<"3 Kez Hayalet �le �arp��t�"<<endl<<"Toplad��� disk say�s�: "<<baslangicDiskSayisi-diskSayisi<<endl<<"Hayaletle �arp��ma say�s�: "<<3-hak<<endl;;
			dosyaAcp.close();
 			cout<<"3 KEZ HAYALET ILE CARPTIGI ICIN YANDI"<<endl;
 			break;	
		}
	}
	
	if(startTime<=0)
	{
		ofstream dosyaAcp;
		dosyaAcp.open("pacmanHareket.txt",ios_base::app);
		dosyaAcp<<"S�re bitti."<<endl<<"Toplad��� disk say�s�: "<<baslangicDiskSayisi-diskSayisi<<endl<<"Hayaletle �arp��ma say�s�: "<<3-hak<<endl;
		dosyaAcp.close();
		cout<<"SURE BITTIGI ICIN OYUN BITTI"<<endl;
		
	}
	
	return 0;
}
