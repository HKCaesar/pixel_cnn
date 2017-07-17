class convolutional_network{
private:
double weight[NO_NEURAN][WEIGHT_COLUMN*WEIGHT_ROW+1];
bool pooling;
double dw[NO_NEURAN][WEIGHT_COLUMN*WEIGHT_ROW+1],grend_total=0;

public:
double ***output;
int ****position;
int x_output,y_output;
float weight_int()
{
    return (rand()%weight_size) * sqrt(2.0/weight_size);
}
float weight_sum(float *s,uint16 x,uint16 y)
{
    uint16 i,j;double temp=0;
    for(i=0;i<x;i++)
        for(j=0;j<x;j++)
            temp+=s[i*y+j];
    return temp;
}
void convolutional_layer(double **input,bool test)
{
    int i,j,k;
    int output_x=!pooling?x_output:(x_output*2),output_y=!pooling?y_output:y_output*2; int i,j,k,l,m,x,y,ppol_x=x_output,pool_y=y_output;
    double temp,sum,grend_total=0,gred;
    for(i=0;i<NO_NEURAN;i++)
    {
        sum=weight_sum(weight[i],WEIGHT_COLUMN,WEIGHT_ROW);

    for(j=0;j<output_x;j++)
    {
    for( k=0;k<output_y;k++)
    {
        temp=0;
        for(l=0;l<WEIGHT_ROW;l++)
            for(m=0;m<WEIGHT_COLUMN;m++)
            {
             temp+=input[j+l][k+m]*weight[i][WEIGHT_COLUMN*l+m];
            }
        temp+=weight[i][WEIGHT_COLUMN*WEIGHT_ROW];
        temp/=sum;
	temp = (1/1+(exp(-temp)));
	if(pool)
	{
	x=j/2;y=k/2;
	if(output[i][x][y]<temp)
	{
         output[i][x][y]=temp;
	 position[i][x][y][0]=j;
	 position[i][x][y][1]=k;
	}
	}
	else
	{
	output[i][j][k]=(1/1+(exp(-output[i][j][k])));
	//gred=0;
    if(!test)
	for(l=0;l<WEIGHT_ROW;l++)
            for(m=0;m<WEIGHT_COLUMN;m++)
            {
             gred=input[j+l][k+m]*output[i][j][k];
	     grend_total+=gred;
	     dw[i][WEIGHT_COLUMN*l+m]+=gred;
            }

	}

    }
    }
    if(!test)
	if(pool)
	for(j=0;j<pool_x;j++)
	for(k=0;k<pool_y;k++)
	{
 	
	 for(l=0;l<WEIGHT_ROW;l++)
            for(m=0;m<WEIGHT_COLUMN;m++)
            {
		gred=input[position[i][j][k][0]+l][position[i][j][k][1]+m]*output[i][j][k];
		dw[i][WEIGHT_COLUMN*l+m]+=gred;
		grend_total+=gred;
            }
	}	
    }
}


void back_propagation(double grant_sum)
{
   // double sum=0.0,total_sum=0.0;
   int i,j,k,l,m;
   for(i=0;i<NO_NEURAN;i++)
       for(j=0;j<WEIGHT_ROW;j++)
           for(k=0;k<WEIGHT_COLUMN;k++)
           {
               weight[i][j*WEIGHT_COLUMN+k]-=LR*dw[j*WEIGHT_COLUMN+k]*grant_sum;
           }
}
double parcial_training(double grent_sum)
{
int i,j,k,l,m;
double totle;
	 for(i=0;i<NO_NEURAN;i++)
       for(j=0;j<WEIGHT_ROW;j++)
           for(k=0;k<WEIGHT_COLUMN;k++)
           {
               totle+=dw[i][j*WEIGHT_COLUMN+k]*=grant_sum;
           }
return total;
}
convolutional_network(int x_input,int y_input,bool pooling)
{
     int output_x=!pooling?x_input-WEIGHT_ROW:(x_input-WEIGHT_ROW)/2;int output_y=!pooling?y_input-WEIGHT_COLUMN:(y_input-WEIGHT_COLUMN)/2,i,j,k;
      if(pooling)
	{
                position=new double***[NO_NEURAN];
	 for(i=0;i<NO_NEURAN;i++)
    	 {
        	 position[i]=new double**[output_x];
        	 for(j=0;j<output_x;j++)
        	 {	
			position[i][j]=new double*[output_y];
			for(k=0;k<output_x;k++)
        	 {	
			position[i][j][k]=new double[2];
			
         	}

         	}
     	}
	
	}
     output=new double**[NO_NEURAN];
     for(i=0;i<NO_NEURAN;i++)
     {
         output[i]=new double*[output_x];
         for(j=0;j<output_x;j++)
         {
             output[i][j]=new double[output_y];
         }
     }
     x_output=output_x;y_output=output_y;
}
};
class deconvolutional_network
{
private:
double weight[NO_NEURAN][WEIGHT_COLUM*WEIGHT_ROW+1];
double dw[NO_NEURAN][WEIGHT_COLUM*WEIGHT_ROW+1];
public:
double ***output,***input;
int x_output,y_output;
void back_propagation(double grant_sum)
{
    double sum=0.0;
   int output_x=(x_output-WEIGHT_ROW),output_y=(y_output-WEIGHT_COLUMN),e,i,j,k,l,m;
   for(i=0;i<NO_NEURAN;i++)
              {
               for(j=0;j<WEIGHT_ROW;j++)
               {

                   for(m=0;m<WEIGHT_COLUMN;m++)
                   {
                     weight[i][WEIGHT_COLUMN*j+m]-=weight[i][WEIGHT_COLUMN*j+m]*dw[i][WEIGHT_COLUMN*j+m]*grant_sum;
		     
                   }

               }

           }
}
	
double parcial_training(double grent_sum)
{
int i,j,k,l,m;
double totle;
	 for(i=0;i<NO_NEURAN;i++)
       for(j=0;j<WEIGHT_ROW;j++)
           for(k=0;k<WEIGHT_COLUMN;k++)
           {
               totle+=dw[i][j*WEIGHT_COLUMN+k]*=grant_sum;
           }
return total;
}
void uppooling_deconvolutional_layer(int ***position,bool test)
{
    double ***out=new double**[NO_NEURAN];
    int x_size=(x_output-WEIGHT_ROW),y_size=(y_output-WEIGHT_COLUMN);
    int output_x=x_size/2,output_y=y_size/2;
    int i,j,k,l,m,e;
   for(e=0;e<NO_NEURAN;e++)
   for(i=0;i<NO_NEURAN;i++)
    for(j=0;j<output_x;j++)
        for(k=0;k<output_y;k++)
        {
	for(l=0;l<WEIGHT_ROW;l++)
               {

                   for(m=0;m<WEIGHT_COLUMN;m++)
                   {

            		output[i][position[i][j][k][0]+k][position[i][j][k][1]+l]+=input[e][j][k]*weight[i][WEIGHT_COLUMN*l+k];
                    if(!test)
		        dw[i][WEIGHT_COLUMN*l+k]+=input[e][j][k];

		  }
       	      }
	}
}

};
