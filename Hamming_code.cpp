#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
int *pin;
int c_nop(int n){
	int i=1;
	while(pow(2,i)<((i+n)+1)){
		i++;
	}
	return i;
}
int isPindex(int in,int nop){
	int i;
	for(i=0;i<nop;i++){
		if(pow(2,i)-1==in)
			return 0;
	}
	return 1;
}
int findP(int in,int *res,int n){
	int i,chk=in,xr=0,ck=1;
//	printf("\n for index[%d]: ",in);
	for(i=in-1;i<n;i++){
		if(ck){
			if(chk!=0){
			//	printf("%d[%d]",i,res[i]);
				xr^=res[i];
				chk--;
				continue;
			}
			ck=0;
		}
		chk++;
		ck=(chk==(in))?1:0;
	}
	//printf("	res::%d",xr);
	return xr;
}
int* sender(int *da,int nop,int n){
	int *res=(int*)malloc((n+nop)*sizeof(int));
	int cnt=n,i=0,j=0,k=0;
	while(cnt!=0){
		if(isPindex(i,nop)){
			res[i++]=da[j++];
			cnt--;
		}else{
			res[i++]=0;
			pin[k++]=i;
		}
		
	}
	printf("\n data [with parity]:");
	for(i=0;i<nop+n;i++)
		printf("%d",res[i]);
	for(i=0;i<nop;i++){
	//	printf("\n ::---->before %d [%d]",pin[i],res[pin[i]]);
		res[pin[i]-1]=findP(pin[i],res,nop+n);
		//printf("\n ::---->after %d [%d]",pin[i],res[pin[i]]);
	}
	printf("\n data [with parity set]:");
	for(i=0;i<nop+n;i++)
		printf("%d",res[i]);
	return res;
}


int RfindP(int in,int *res,int n){
	int i,chk=in,xr=0,ck=1;
//	printf("\n for index[%d]: ",in);
	for(i=in-1;i<n;i++){
		if(ck){
			if(chk!=0){
			//	printf("%d[%d]",i,res[i]);
				xr^=res[i];
				chk--;
				continue;
			}
			ck=0;
		}
		chk++;
		ck=(chk==(in))?1:0;
	}
	//printf("	res::%d",xr);
	return xr;
}

void receiver(int *da,int nop,int n){
	int i,r=0;
	for(i=0;i<(nop);i++){
		r=r+pow(2,i)*RfindP(pin[i],da,nop+n);
	}
	if(r==0){
		printf("\n DATA RECEIVED SUCCESS FULLY");
	}else{
		printf("\n ! DATA CURROPTED AT INDEX : %d",r);
	}
	
}
int main(){
	int nop,data[20],n,i,res[20],*te;
	char t[20];
	printf("\n enter the length of data:");
	scanf("%d",&n);
	printf("\n enter the data:");
	scanf("%s",t);
	for(i=0;i<n;i++)
		data[i]=t[i]-'0';
	nop=c_nop(n);
	pin=(int*)malloc(nop*(sizeof(int)));
	printf("\n NO OF PARITY : %d",nop);
	te=sender(data,nop,n);
//	te[2]=!te[2];
	receiver(te,nop,n);
	return 0;
}
