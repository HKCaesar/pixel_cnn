
class convolutional_network{
public:
double weight[NO_NEURAN][WEIGHT_COLUMN*WEIGHT_ROW+1];

double ***output;
int x_output,y_output;

double weight_int()
{
    double x=(rand()%WEIGHT_SIZE) * sqrt(2.0/WEIGHT_SIZE);
    return x;
}
double weight_sum(int s)
{
    int i,j=WEIGHT_ROW*WEIGHT_COLUMN+1;double temp=0;

    for(i=0;i<j;i++)
        //for(j=0;j<WEIGHT_COLUMN;j++)
            temp+=weight[s][j];
    return temp;
}

void convolutional_layer(double **input)
{

    int output_x=x_output,output_y=y_output,i,j,k,l,m;
    //cout<<x_output;
    output=new double**[NO_NEURAN];
    for(i=0;i<NO_NEURAN;i++)
    {
        output[i]=new double*[output_x];
        for(j=0;j<output_x;j++)
        {
            output[i][j]=new double[output_y];
        }
    }

    double temp,sum;
    for(i=0;i<NO_NEURAN;i++)
    {
        sum=weight_sum(i);

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
         output[i][j][k]=temp;
         output[i][j][k]=(1/1+(exp(-output[i][j][k])));

    }
    }
    }
}


double back_propagation(double grant_sum,double **input)
{
    double sum=0.0,total_sum=0.0;
   int output_x=x_output,output_y=y_output,i,j,k,l,m;
   for(i=0;i<NO_NEURAN;i++)
   {
       for(j=0;j<WEIGHT_ROW;j++)
           for(k=0;k<WEIGHT_COLUMN;k++)
           {
               for(l=0;l<output_x;l++)
               {

                   for(m=0;m<output_y;m++)
                   {
                     sum+=input[l+j][m+k]*output[i][j][k];
                   }

               }
               weight[i][j*WEIGHT_COLUMN+k]-=LR*sum*grant_sum;
               total_sum+=sum;
               sum=0.0;
           }
       weight[i][WEIGHT_ROW*WEIGHT_COLUMN]-=LR*grant_sum;
   }
   return total_sum;
}

int**** pooling()
{

   // cout<<x_output;
    int ****position;
    int output_x=x_output,output_y=y_output,i,j,k,l,m,pool_image_x=x_output/POOL_SIZE,pool_image_y=y_output/POOL_SIZE,temp_x,temp_y;
    double ***out=new double**[NO_NEURAN],max;
    position=new int***[NO_NEURAN];
   //cout<<x_output;

    //int pool_x=0,pool_y=9;

    for(i=0;i<NO_NEURAN;i++)
    {
        out[i]=new double*[pool_image_x];
        position[i]=new int**[pool_image_x];
        for(j=0;j<pool_image_x;j++)
        {
            out[i][j]=new double[pool_image_y];
            position[i][j]=new int*[pool_image_y];
            for(k=0;k<pool_image_y;k++)
            {
                position[i][j][k]=new int[2]();

            }
           // cout<<j<<"\t"<<k<<"\n";
        }
    }
//cout<<pool_image_x<<"\t"<<pool_image_y;
    for(i=0;i<NO_NEURAN;i++)
    {
        //pool_x=0;

        for(j=0;j<pool_image_x;j++)
        {



           for(k=0;k<pool_image_y;k++)
            {
               for(l=j*POOL_SIZE;l<j*POOL_SIZE+POOL_SIZE;l++)
               {

                   for(m=k*POOL_SIZE;m<j*POOL_SIZE+POOL_SIZE;m++)
                   {
                        if(l==0&&m==0)
                         {
                            max =output[i][l][k];
                            temp_x=l;
                            temp_y=m;
                        }

                        else if(max<output[i][l][m])
                        {
                            max =output[i][l][m];
                            temp_x=l;
                            temp_y=m;
                           // cout<<"gASGJHAgjhas";
                        }
                        //cout<<"gASGJHAgjhas";
                       // cout<<temp_x<<"\t"<<temp_y<<"\n";
                   }

               }

               out[i][j][k]=max;
               position[i][j][k][0]=temp_x;
               position[i][j][k][1]=temp_y;



            }

        }
    }
//cout<<pool_x<<"\t"<<pool_y;
   // cout<<"Delete output\n";

    for(i=0;i<NO_NEURAN;i++)
    {
        for(j=0;j<output_x;j++)
           //for(k=0;k<output_y;k++)
            {

             delete[]  output[i][j];
          //  free(output[i][j]);
            }
                    delete[]  output[i];
       // free(output[i]);
    }
    delete[] output;
     output=out;
    return position;
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
                      weight[j][k]=weight_int();

                }


           }


}

convolutional_network(int x_input,int y_input)
{
     int output_x=x_input-WEIGHT_ROW;int output_y=y_input-WEIGHT_COLUMN,i,j;

     x_output=output_x;y_output=output_y;
    // cout<<x_output<<"\n";
     init_weight();
}
};
class deconvolutional_network
{
public:
double weight[NO_NEURAN][WEIGHT_COLUMN*WEIGHT_ROW+1];

double ***output,***input;
int x_output,y_output;
float weight_int()
{
    return (rand()%WEIGHT_SIZE) * sqrt(2.0/WEIGHT_SIZE);
}
double weight_sum(double *s)
{
    int i,j;double temp=0;
    for(i=0;i<WEIGHT_ROW;i++)
        for(j=0;j<WEIGHT_COLUMN;j++)
            temp+=s[i*WEIGHT_COLUMN+j];
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

void deconvolutional_layer()
{
    int x_size=x_output-WEIGHT_ROW,y_size=y_output-WEIGHT_COLUMN,e,i,j,k,l,m;
    double temp;
    for(e=0;e<NO_NEURAN;e++)
    for(i=0;i<NO_NEURAN;i++)
    {
        //double sum=weight_sum(weight[i],WEIGHT_COLUMN,WEIGHT_ROW);

    for(j=0;j<x_size;j++)
    {
    for( k=0;k<y_size;k++)
    {
        temp=0;
        for(l=0;l<WEIGHT_ROW;l++)
            for(m=0;m<WEIGHT_COLUMN;m++)
            {
             output[i][j+l][k+m]+=input[e][j][k]*weight[i][WEIGHT_COLUMN*l+m];
            }

    }
    }
    }

}
double back_propagation(double grant_sum)
{
    double sum=0.0;
   int output_x=(x_output-WEIGHT_ROW),output_y=(y_output-WEIGHT_COLUMN),e,i,j,k,l,m;

   for(e=0;e<NO_NEURAN;e++)
              {
                sum=0;
               for(l=0;l<output_x;l++)
               {

                   for(m=0;m<output_y;m++)
                   {
                     sum+=input[e][l][m];
                   }

               }
           }
   for(i=0;i<NO_NEURAN;i++)
              {
               for(j=0;j<WEIGHT_ROW;j++)
               {

                   for(m=0;m<WEIGHT_COLUMN;m++)
                   {
                     weight[i][WEIGHT_COLUMN*j+m]-=LR*sum*grant_sum;
                   }

               }

           }
   return sum;
}
void uppooling(int ****position)
{
    double ***out=new double**[NO_NEURAN];
    int x_size=(x_output-WEIGHT_ROW),y_size=(y_output-WEIGHT_COLUMN),posion_x,posion_y;
    int output_x=x_size/2,output_y=y_size/2;
    int i,j,k;
    for(i=0;i<NO_NEURAN;i++)
    {
        out[i]=new double*[x_size];
        for(j=0;j<x_size;j++)
            out[i][j]=new double[y_size];
    }

   for(i=0;i<NO_NEURAN;i++)
    for(j=0;j<output_x;j++)
        for(k=0;k<output_y;k++)
        {
            //cout<<position[i][j][k][0]<<"\t"<<position[i][j][k][1]<<"\n";
            out[i][position[i][j][k][0]][position[i][j][k][1]]=input[i][j][k];
        }
/*
   for(i=0;i<NO_NEURAN;i++)
   {
        //for(k=0;k<output_y;k++)
       for(j=0;j<output_x;j++)
        //{
             delete[] input[i][j];
        //}
             delete[] input[i];
   }
    delete[] input;
    */
    input=out;
}
deconvolutional_network(int x_input,int y_input)
{
    int output_x=x_input;int output_y=y_input,i,j;
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
    init_weight();
}

};
void uppooling(double **input,int &x_input,int &y_input,int ***position)
{
    double **out=new double*[x_input*2];
    int x_size=x_input*2,y_size=y_input*2;
    int i,j;
    for(i=0;i<x_size;i++)
        out[i]=new double[y_size]();
    for(i=0;i<x_input;i++)
        for(j=0;j<y_input;j++)
        {
            out[position[i][j][0]][position[i][j][1]]=input[i][j];
        }
    delete[] input;
    input=out;
    x_input=x_size;y_input=y_size;
}

