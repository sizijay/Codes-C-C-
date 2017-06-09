#include <stdio.h>
#include <string.h>


void SpecialSearch(char *pattern1, char *pattern2, char *text){
  int LocP1;
  int LocP2;
  int Lp = strlen(pattern1);
  //int Lp2 = strlen(pattern2);
  int Lt = strlen(text);
  int count = 0;

  int i;
  int j;
  for(i=0;i<=Lt-Lp;i++){
    for(j=0;j<Lp;j++){
        if(text[i+j]!= pattern1[j])
            break;
        
        if(j==Lp-1){
            printf("%s Found at index %d \n",pattern1,i);
            LocP1 = i;
        }
    }
  }



  int k;
  int l;
  for(k=0;k<=Lt-Lp;k++){
    for(l=0;l<Lp;l++){
        if(text[k+l]!=pattern2[l]){
            break;
        }
        if(l==Lp-1){
            printf("%s Found at index %d \n",pattern2,k);
            LocP2 = k;
        }
    }
    
  }
  if(LocP1<LocP2 && count==0){
        printf("True\n");
        count+=1;
    }

  else if(count == 0){
    printf("False\n");
    count++;
  }
}

int main()
{
    char pattern1[] = "AB";
    char pattern2[] = "CD";
    char text[] = "EF CD AB CD";

    SpecialSearch(pattern1,pattern2,text);
    return 0;
}
