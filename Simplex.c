//TO COMPILE :
//NAVIGATE TO THE FILE LOCATION WITH 'TERMINAL'
//AND COMPILE IT WITH
//  'gcc 15000648.c -o 15000648'
//THEN RUN IT WITH
// './15000648'
//CAN USE ANY NAME AS THE COMPILED FILE WHEN COMPILING


#include<stdio.h>
#include<math.h>

//maximum number of constraints 
#define cons 10    

//maximum number of variables in the main function
#define vbls 10    

void Data();          
void PivotValue();
void Formula();
void Optimize();
void SimplexAlgo();
void FinalResults();

//declare needed variables
int Ncons, Nvbls, Opt,PLine,PIdx,NoSol;

//Simplex table  
double tableS[cons][vbls];    




void Data(){

	double max,min;
	char Selec;
	int i,j;
	
	printf("\n Enter >>> \n\t'1' to Maximize\n\t'2' to Minimize\n\t\t>>>  ");
	scanf("%c", &Selec);

	printf("\n Enter the number of variables in Main function >>>  "); 
	scanf("%d" , &Nvbls);

	printf("\n Enter the number of constraints >>> "); 
	scanf("%d" ,&Ncons);


	//Identifying whether Maximize or Minimize
	if(Selec=='1'){
		max = 1.0;
	}
	else if(Selec=='2'){
		max = -1.0;
	}

	printf("\n Enter the co-efficients of Main function: \n");

	//fill the table with coeffitients in main function
	for(j=1;j<=Nvbls ; j++){
		printf(" #X %d ? ", j);
		scanf("%lf", &min);
		tableS[1][j+1] = min*max;    
	}

	//add the value in right hand side of main function to the table
	printf(" Enter the value in Right hand side >>> ");
	scanf("%lf",&min);
	tableS[1][1] = min*max;		

	for(i=1;i<=Ncons;i++){
		printf("\n Enter the values of constraints %d:\n",i);

		//fill the table from coefficients from constraints function
		for(j=1;j<=Nvbls;j++){
			printf(" # X%d ? ",j);
			scanf("%lf", &min);
			tableS[i+1][j+1] = -min;   
		}

		//add the value in right hand side of main function to the table
		printf(" Enter the value in Right hand side >>> ");
		scanf("%lf",&tableS[i+1][1]);     
	}

	printf("\n\n Final Results:\n\n");
	
	for(j=1; j<=Nvbls ; j++){
		tableS[0][j+1] =j;
	}
	for(i=Nvbls+1; i<= Nvbls+Ncons; i++){
		tableS[i-Nvbls+1][0] = i;	
	}
	
	//print the  Simplex table
	for(i=0; i<=Ncons+1; i++){
		for(j=0; j<=Nvbls+1; j++){
			printf("\t%lf ", tableS[i][j]);
		}
		printf("\n\n");
	}
}

//assign pivot values
void PivotValue(){
	double ratio,aux,maxCoe;
	int i,j;

	maxCoe = 0.0;
	for(j=2; j<=Nvbls+1; j++){
		if(tableS[1][j] > 0.0 && tableS[1][j] > maxCoe){
			maxCoe = tableS[1][j];
			PIdx = j;
		}
	}
	

	ratio = 99999999.0;
	
	for(i=2; i<=Ncons+1; i++){
		if(tableS[i][PIdx]>=0.0){
			goto e10;
		}
		aux = fabs(tableS[i][1] / tableS[i][PIdx]);
		printf("\tAuxilary Variable is %lf\n",aux);
		if(aux<ratio){
			ratio = aux;
			PLine = i;
		}
	
	e10: ; 
	}
	
	aux = tableS[0][PIdx];
	tableS[0][PIdx] = tableS[PLine][0];
	tableS[PLine][0] = aux;

	
}

//apply the Simplex algorithm and call other methods
void SimplexAlgo(){
	e10: PivotValue();  
	Formula();
	Optimize();
	if(Opt == 1){
		goto e10;
	}
}


//apply the formula to the values taken
void Formula(){
	
	int i,j;
	
	for(i=1; i<=Ncons+1; i++){
		if(i==PLine){
			goto e70;
		}
		for(j=1; j<=Nvbls+1; j++){
			if(j==PIdx){
				goto e60;
			}
			tableS[i][j] -= tableS[PLine][j]*tableS[i][PIdx] / tableS[PLine][PIdx];
		e60: ; 
		}
	e70: ;  
	}

	tableS[PLine][PIdx] = 1.0 / tableS[PLine][PIdx];
	for(j=1; j<=Nvbls+1; j++){
		if(j==PIdx){
			goto e100;
		}
		tableS[PLine][j] *= fabs(tableS[PLine][PIdx]);
	e100: ;    
	}

	for(i=1; i<=Ncons+1;i++){
		if(i==PIdx){
			goto e110;
		}
		tableS[i][PIdx] *= tableS[PLine][PIdx];
	e110: ;    
	} 
			
}

//optimization method
void Optimize()
{
	int i,j;
	for(i=2; i<=Ncons+1; i++){
		if(tableS[i][1] < 0.0){
			NoSol = 1;
		}
	}
	Opt = 0;
	if(NoSol ==1){
		return;
	}
	for(j=2; j<=Nvbls+1; j++){
		if(tableS[1][j] > 0.0){
			Opt = 1;
		}
	}
	
			
}	

//get the final results and print the final results
void FinalResults()
{
	//labels
	int i,j;

	if(NoSol == 0){
		goto e30;
	}
	printf(" Solution does not Exist.\n");
	goto e100;


e30:    for(i=1; i<=Nvbls; i++){      
		for(j=2; j<=Ncons; j++){
			if(tableS[j][0] != 1.0*i){
				goto e70;
			}
			printf("\n\tVariable # X%d: %f\n", i, tableS[j][1]);
		e70: ;  
		}
	}
	printf("\n\tFinal Value , Main Function : %f\n", tableS[1][1]);
	
e100: printf("\n");
	
}

int main(){
	printf("\n\n===================================================================\n------------------------ Simplex Algorithm ------------------------\n===================================================================\n");
	Data();
	SimplexAlgo();
	FinalResults();
	return 0;

}


// 	PLine,PIdx 	: line , column index of Pivot 
// 	NoSol  		: Boolean, if true No solution 
// 	max    		: = 1 for maximize, = -1 for minimize 
// 	min    		: auxilary variable for inputs 
// 	Opt 		: Boolean, if false continue iterations 
//  Ncons   	: Number of constraints 
//  Nvbls   	: Number of variables in main function 
// 	tableS 		: simplex tableS of size NC+1 x Nvbls+1 
//  ratio  		: stores smallest ratio >0 
// 	maxCoe  	: stores greatest coeffitient of main function 
// 	aux    		: auxilary variable  

