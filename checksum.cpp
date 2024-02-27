#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

int* sender_csum(int *a,int *b,int n){
	int c=0,*t=(int*)malloc(n*(sizeof(int)));
	int i,te;
	for(i=n-1;i>=0;i--){
		t[i]=a[i]^b[i]^c;
		if((a[i]&b[i])||(a[i]&c)||b[i]&c){
			c=1;
		}else{
			c=0;
		}
	}
	i=n-1;
	while(c!=0){
		te=t[i];
		t[i]^=c;
		c&=te;
		i=(i==0)?n-1:i-1;
	}
	printf("\nthe sum [SENDER]:");
	for(i=0;i<n;i++){
		printf("%d",t[i]);
	}
	for(i=0;i<n;i++){
		t[i]=!t[i];
	}
	printf("\n check sum:");
	for(i=0;i<n;i++){
		printf("%d",t[i]);
	}
	return t;
}

void receiver(int *a,int *b,int n,int *cs){
		int c=0,*t=(int*)malloc(n*(sizeof(int)));
	int i,te;
	for(i=n-1;i>=0;i--){
		t[i]=a[i]^b[i]^c;
		if((a[i]&b[i])||(a[i]&c)||b[i]&c){
			c=1;
		}else{
			c=0;
		}
	}
	i=n-1;
	while(c!=0){
		te=t[i];
		t[i]^=c;
		c&=te;
		i=(i==0)?n-1:i-1;
	}
	printf("\nthe sum [RECIVER]:");
	for(i=0;i<n;i++){
		printf("%d",t[i]);
	}
	c=0;
	printf("\n detection:");
	for(i=n-1;i>=0;i--){
		//printf("\n t :%d cs :%d c :%d",t[i],cs[i],c);
		te=t[i];
		t[i]=t[i]^cs[i]^c;
		if((te&cs[i])||(te&c)||cs[i]&c){
			c=1;
		}else{
			c=0;
		}
		//printf("   res :%d",t[i]);
	}
	for(i=0;i<n;i++)
		if(t[i]==0){
			printf("\n!!DATA CORRUPTED");
			return;
		}
	printf("\n DATA RECIVED SUCCESS FULLY!");
}

int main(){
	int *t,a[10],b[10],i,n;
	char te[10];
	printf("\n enter size of segment:");
	scanf("%d",&n);
	printf("\n enter segment 1:");
	scanf("%s",te);
	for(i=0;i<n;i++)
		a[i]=te[i]-'0';
	printf("\n enter segment 2:");
	scanf("%s",te);
	for(i=0;i<n;i++)
		b[i]=te[i]-'0';
	t=sender_csum(a,b,n);
	receiver(a,b,n,t);
	return 0;
	
	
}
