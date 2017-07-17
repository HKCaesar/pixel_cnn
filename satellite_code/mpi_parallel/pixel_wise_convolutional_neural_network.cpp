
class opt_convolutional_network{
private:
double weight[NO_NEURAN][WEIGHT_COLUMN*WEIGHT_ROW+1];
bool pool;
double dw[NO_NEURAN][WEIGHT_COLUMN*WEIGHT_ROW+1];

public:
double ***output,gradent_sum=0.0;
int ****position;
//double ***dw;
//int ****position;
int x_output,y_output;

double weight_int()
{
    //cout<<WEIGHT_SIZE;
    double x=(rand()%WEIGHT_SIZE) * sqrt(2.0/WEIGHT_SIZE);
   // cout<<x;
    return x;
}
double weight_sum(int i)
{
    double temp=0;
    int j,weight_size=WEIGHT_COLUMN*WEIGHT_ROW+1 ;

        for(j=0;j<weight_size;j++)
        {
           // cout<<"Hello";
           // cout<<s[i*WEIGHT_COLUMN+j];
            temp+=weight[i][j];
        }

//cout<<temp;
    return temp;
}
void out_put_reset()
{
    int i,j,k,weight_size=WEIGHT_COLUMN*WEIGHT_ROW+1;
    uint16 output_x=x_output,output_y=y_output;
    double total=0;
     for(i=0;i<NO_NEURAN;i++)
    for(j=0;j<output_x;j++)
    {
        for(k=0;k<output_y;k++)
        output[i][j][k]=0;
    }
}

void convolutional_layer_pool(double **input,bool test)
{

    int output_x=!pool?x_output:x_output*POOL_SIZE,output_y=!pool?y_output:y_output*POOL_SIZE,i,j,k,l,m,x,y,cr,cc,temp_x,temp_y;
    //cout<<x_output;
   // output=new double**[NO_NEURAN];

    out_put_reset();

    double *result;//=new double[output_y];
    double temp,sum,grent=0;

    if(!pool)
    {
       // if(!test)
        double temp_dw[WEIGHT_COLUMN*WEIGHT_ROW];
    for(i=0;i<NO_NEURAN;i++)
    {
        sum=weight_sum(i);
       // cout<<sum;

    for(j=0;j<output_x;j++)
    {
    for( k=0;k<output_y;k++)
    {
        temp=0;


        for(l=0;l<WEIGHT_ROW;l++)
            for(m=0;m<WEIGHT_COLUMN;m++)
            {
             temp+=input[j+l][k+m]*weight[i][WEIGHT_COLUMN*l+m];
             if(!test)
             temp_dw[WEIGHT_COLUMN*l+m]=input[j+l][k+m];
            }
        temp+=weight[i][WEIGHT_COLUMN*WEIGHT_ROW];
        temp/=sum;

        temp=(1/1+(exp(-temp)));
        if(!test)
        for(l=0;l<WEIGHT_ROW;l++)
            for(m=0;m<WEIGHT_COLUMN;m++)
            {
            //temp+=input[j+l][k+m]*weight[i][WEIGHT_COLUMN*l+m];
             dw[i][WEIGHT_COLUMN*l+m]+=temp_dw[WEIGHT_COLUMN*l+m]*temp;
             grent+=temp_dw[WEIGHT_COLUMN*l+m]*temp;
            }
         output[i][j][k]+=temp;
         //output[i][j][k]=(1/1+(exp(-output[i][j][k])));
    }
    }
    }
    }
    else
    {
        result=new double[output_y];

        for(i=0;i<NO_NEURAN;i++)
        {
            sum=weight_sum(i);

        for(j=0;j<output_x;j++)
        {
            x=output_x/POOL_SIZE;
        for( k=0;k<output_y;k++)
        {
            temp=0;
            y=output_y/POOL_SIZE;

              for(l=0;l<WEIGHT_ROW;l++)
                for(m=0;m<WEIGHT_COLUMN;m++)
                {
                 temp+=input[j+l][k+m]*weight[i][WEIGHT_COLUMN*l+m];

                }
            temp+=weight[i][WEIGHT_COLUMN*WEIGHT_ROW];
            temp/=sum;
            temp=(1/1+(exp(-temp)));
                  if(temp>result[y])
                  {
                      result[y]=temp;
                      if(!test)
                      {
                          temp_x=j;
                          temp_y=k;
                      }

                  }
                  if((j+1)%POOL_SIZE==0)
                  {

                      output[i][x][y]=result[y];
                      position[i][x][y][0]=temp_x;position[i][x][y][1]=temp_y;
                      if(!test)
                      {
                          for(l=0;l<WEIGHT_ROW;l++)
                              for(m=0;m<WEIGHT_COLUMN;m++)
                              {
                              //temp+=input[j+l][k+m]*weight[i][WEIGHT_COLUMN*l+m];
                               dw[i][WEIGHT_COLUMN*l+m]+=input[temp_x+l][temp_y+m]*result[y];
                              }
                          grent+=input[temp_x+l][temp_y+m]*result[y];
                      }
                  }
             //output[j][k]+=temp;
             //output[i][j][k]=(1/1+(exp(-output[i][j][k])));

        }


        }
        }
    }
    gradent_sum=grent;

}

void persial_training(double grant_sum)
{
    double sum=0.0,total_sum=0.0;
   int output_x=x_output,output_y=y_output,i,j,k,l,m;
   for(i=0;i<NO_NEURAN;i++)
   {
       for(j=0;j<WEIGHT_ROW;j++)
           for(k=0;k<WEIGHT_COLUMN;k++)
           {
               dw[i][j*WEIGHT_COLUMN+k]*=grant_sum;
               //sum+=dw[i][j*WEIGHT_COLUMN+k];

           }

   }
   //return sum;

}

void back_propagation(double grant_sum)
{
    double sum=0.0,total_sum=0.0;
   int output_x=x_output,output_y=y_output,i,j,k,l,m;
   for(i=0;i<NO_NEURAN;i++)
   {
       for(j=0;j<WEIGHT_ROW;j++)
           for(k=0;k<WEIGHT_COLUMN;k++)
           {               
               weight[i][j*WEIGHT_COLUMN+k]-=LR*dw[i][j*WEIGHT_COLUMN+k]*grant_sum;
               //total_sum+=sum;
               //sum=0.0;
           }
       weight[i][WEIGHT_ROW*WEIGHT_COLUMN]-=LR*grant_sum;
   }
   //return total_sum;
}


void init_weight()
{
    //weight_size=125;
           uint16 i,j,k,m;
           uint16 weight_size=WEIGHT_COLUMN*WEIGHT_ROW+1 ;
           //weight=new float*[NO_NEURAN];
           //cout<<weight_size;
           for(j=0;j<NO_NEURAN;j++)
           {

           //    break;
             //  weight[j]=new float[WEIGHT_COLUMN*WEIGHT_ROW+1];
               //cout<<"Hello"<<in_rows;
               for( k=0;k<weight_size;k++)
                {
                      weight[j][k]=weight_int();//cout<<"Hello"<<weight[j][k];

                }


           }


}

opt_convolutional_network(int x_input,int y_input,bool pooling)
{
    // int output_x=x_input-WEIGHT_ROW;int output_y=y_input-WEIGHT_COLUMN,i,j;
     //x_output=output_x/POOL_SIZE;y_output=output_y/POOL_SIZE;
    x_input-=WEIGHT_ROW;y_input-=WEIGHT_COLUMN;
     int output_x=!pooling?x_input:x_input/POOL_SIZE ,output_y=!pooling?y_input:y_input/POOL_SIZE,i,j,k;
    pool=pooling;
    output=new double**[NO_NEURAN];
    if(pooling)
    {
        position=new int***[NO_NEURAN];

        for(i=0;i<NO_NEURAN;i++)
        {
                position[i]=new int**[output_x];
                output[i]=new double*[output_x];
            for(j=0;j<output_x;j++)
            {
                position[i][j]=new int*[output_y];
                output[i][j]=new double[output_y]();

                for(k=0;k<output_y;k++)
                {
                    position[i][j][k]=new int[2]();
                }
            }
        }
    }
     else
      for(i=0;i<NO_NEURAN;i++)
      {
          output[i]=new double*[output_x];
     for(k=0;k<output_x;k++)
     {
           output[i][k]=new double[output_y]();


      }

     x_output=output_x;y_output=output_y;

    // cout<<x_output<<"\n";
     init_weight();
}
}
};
class opt_deconvolutional_network
{
public:
double weight[NO_NEURAN][WEIGHT_COLUMN*WEIGHT_ROW+1];
double dw[NO_NEURAN][WEIGHT_COLUMN*WEIGHT_ROW+1],gradent_sum=0.0;

double ***output,***input;
int x_output,y_output,input_x,input_y,****position;
private:
bool upooling;
void out_put_reset()
{
    int i,j,k;
    int output_x=x_output,output_y=y_output;
    //cout<<output_x<<"\t"<<output_y;

     for(i=0;i<NO_NEURAN;i++)
    for(j=0;j<output_x;j++)
    {
        for(k=0;k<output_y;k++)
        output[i][j][k]=0;
    }

}
public:
void persial_training(double grant_sum)
{
   // double sum=0.0,total_sum=0.0;
   int output_x=x_output,output_y=y_output,i,j,k,l,m;
   for(i=0;i<NO_NEURAN;i++)
   {
       for(j=0;j<WEIGHT_ROW;j++)
           for(k=0;k<WEIGHT_COLUMN;k++)
           {
                //sum+=dw[i][j*WEIGHT_COLUMN+k];
               dw[i][j*WEIGHT_COLUMN+k]*=grant_sum;


           }

   }
  // return sum;

}
double weight_int()
{
   double x= (rand()%WEIGHT_SIZE) * sqrt(2.0/WEIGHT_SIZE);
    return x;
}
double weight_sum(int i)
{
    uint16 j, weight_size=WEIGHT_COLUMN*WEIGHT_ROW+1 ;

    double temp=0;

        for(j=0;j<weight_size;j++)
            temp+=weight[i][j];
    return temp;
}
void init_weight()
{
    //weight_size=125;
           uint16 i,j,k,m;
           int weight_size=WEIGHT_COLUMN*WEIGHT_ROW+1 ;
           //weight=new double*[NO_NEURAN];
           //cout<<weight_size;
           for(j=0;j<NO_NEURAN;j++)
           {

           //    break;
             //  weight[j]=new double[weight_size];
               //cout<<"Hello"<<in_rows;
               for( k=0;k<weight_size;k++)
                {
                      weight[j][k]=weight_int();

                }


           }


}
public:

void deconvolutional_layer(bool test)
{
    int x_size=input_x,y_size=input_y,e,i,j,k,l,m,o,p;
    double temp,sum=0;
    out_put_reset();

    if(!upooling)

    for(i=0;i<NO_NEURAN;i++)
    {
        //double sum=weight_sum(weight[i],WEIGHT_COLUMN,WEIGHT_ROW);

    for(j=0;j<x_size;j++)
    {
    for( k=0;k<y_size;k++)
    {
        temp=0;
        for(e=0;e<NO_NEURAN;e++)
        {
            temp+=input[e][j][k];
        }
        for(l=0;l<WEIGHT_ROW;l++)
            for(m=0;m<WEIGHT_COLUMN;m++)
            {
             output[i][j+l][k+m]+=temp*weight[i][WEIGHT_COLUMN*l+m];
             if(!test)

             {
                 dw[i][WEIGHT_COLUMN*l+m]+=temp;
                 sum+=temp;
             }
            }

    }
    }
    }
    else
    {

        for(i=0;i<NO_NEURAN;i++)
        {
            //double sum=weight_sum(weight[i],WEIGHT_COLUMN,WEIGHT_ROW);

        for(j=0;j<x_size;j++)
        {
        for( k=0;k<y_size;k++)

            {

            temp=0;
            for(o=j*POOL_SIZE;o<(j+1)*POOL_SIZE;o++)
                for(p=k*POOL_SIZE;p<(k+1)*POOL_SIZE;p++)
                {
                    for(e=0;e<NO_NEURAN;e++)
                        if(position[e][j][k][0]==o&&position[e][j][k][1]==p)
                        temp+=input[e][j][k];
            for(l=0;l<WEIGHT_ROW;l++)
                for(m=0;m<WEIGHT_COLUMN;m++)
                {
                 output[i][o+l][p+m]+=temp*weight[i][WEIGHT_COLUMN*l+m];
                 if(!test)
                 {
                 dw[i][WEIGHT_COLUMN*l+m]+=temp;
                 sum+=temp;
                 }
                }
                }

            }
        }
        }
    }
    gradent_sum=sum;

}

void back_propagation(double grant_sum)
{
    double sum=0.0;
   int i,j,m;


   for(i=0;i<NO_NEURAN;i++)
              {
               for(j=0;j<WEIGHT_ROW;j++)
               {

                   for(m=0;m<WEIGHT_COLUMN;m++)
                   {
                     weight[i][WEIGHT_COLUMN*j+m]-=LR*dw[i][WEIGHT_COLUMN*j+m]*grant_sum;
                   }

               }

           }
   //return sum;
}

opt_deconvolutional_network(int x_input,int y_input,bool uppooling)
{
    int output_x=!uppooling?x_input:x_input*POOL_SIZE,output_y=!uppooling?y_input:y_input*POOL_SIZE,i,j;
    output=new double**[NO_NEURAN];output_x+=WEIGHT_ROW;output_y+=WEIGHT_COLUMN;
    for(i=0;i<NO_NEURAN;i++)
    {
        output[i]=new double*[output_x];
        for(j=0;j<output_x;j++)
        {
            output[i][j]=new double[output_y]();
        }
    }
    x_output=output_x;y_output=output_y;
    input_x=x_input;input_y=y_input;
    init_weight();
}

};
