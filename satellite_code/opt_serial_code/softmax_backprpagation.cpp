
class serial_softmax_error
{
private:
    uint16 image_x,image_y;
    //double *weight;
    double **output;
     uint16 weight_size ;

public:
    double avg=0;double *weight;
    /*
     * For Soft max****
    double** fully_connection_by_softmax(uint16 xd,uint16 yd,double **x)
    {
                double sum=0;
                double **s=new double*[xd]();
                uint16 i,j;
                for(i=0;i<xd;i++)
                {
                    s[i]=new double[yd]();
                    for(j=0;j<yd;j++)
                    sum=exp(x[i][j])+sum;
                }
               for(i=0;i<xd;i++)for(j=0;j<yd;j++)s[i][j]=exp(x[i][j])/sum;
               return s;
    }
    /*
     * Flowing function is a folt function need to deal with it later
     * couse of fault softmax function only cheack whether out put is a spacific
     * class or not.It is not good for mixe kind of image for clasification.
     * As it need to maintain multipal train image for each class.
    double** derivation_softmax(double **s,uint16 x_num_class,uint16 y_num_class){
        double **dsdf=new double*[x_num_class];

        uint16 i,j,o,p;
        for(i=0;i<y_num_class;i++)
            dsdf[i]=new double[y_num_class];
        for(i=0;i<x_num_class;i++)
          for (j=0;j<y_num_class;j++)
              for(o=0;o<x_num_class;o++)
                  for(p=0;p<y_num_class;p++)
                      if((i==o)&&(j==p))
                          dsdf[i][j] =dsdf[i][j]+ s[i][j]*(1-s[i][j]);
                      else
                          dsdf[i][j]=dsdf[i][j]-(s[i][j]*s[o][p]);
        return dsdf;
    }
    double** error_fun_for_softmax(double** t,double** out,uint16 x_cl,uint16 y_cl){
     double total=0.0;
       uint16 i,j;
     double **e=new double*[x_cl]();
     for (i=0;i++;i<x_cl)
     {
         e[i]=new double[y_cl]();
         for(j=0;j<x_cl;j++)
            {
             e[i][j]=-t[i][j]*(log(out[i][j]));
            }
     }
     return e;
    }

    uint16** test_class_for_softmax(double** out,uint16 x_cl,uint16 y_cl,uint16 num_class){
     double total=0.0;
     avg=0.0;
       uint16 i,j,k;
     uint16 **t=new uint16*[x_cl]();
     double temp=0.0;
     uint16 temp_cl=0;
     for (i=0;i++;i<x_cl)
     {
         t[i]=new uint16[y_cl]();
         for(j=0;j<x_cl;j++)
            {
             for(k=1;k<=num_class;k++)
             if(temp>-num_class*(log(out[i][j])))
             {
                    temp=-temp_cl*(log(out[i][j]));
                    temp_cl=k;
             }
             t[i][j]=temp_cl;
             avg=avg+temp/(x_cl+y_cl);
            }
     }
     return t;
    }*/

/*
 *
 * For SVM  *
 * */


/* I will see it later
    double** error_svm(double **t,double **out,uint16 x_cl,uint16 y_cl){
      double total=0.0;uint16 i,j,o,p;
        double **e=new double*[x_cl]();
        for(i=0;i<x_cl;i++)e[i]=new double[y_cl];
        for (i=0;i<x_cl;i++)
            for(j=0;j<y_cl;j++)
                {
                for (o=0;o<x_cl;o++)
                    for(p=0;p<y_cl;p++)

                {
                    if((i==o)&&(j==p))
                    continue;
                    total =total+ std::max(0.0,(out[o][p]-t[i][j]+100.0));
                }
            e[i][j]=total;
        }
        return e;

    }

    double** dirivation_error_svm(double** t,double** out,uint16 x_cl,uint16 y_cl){
        double **dedout=new double*[x_cl]();
        double total = 0.0;
        double **e=error_svm(t,out,x_cl,y_cl);
        uint i,j,o,p;
        for(i=0;i<x_cl;i++)dedout[i]=new double[y_cl]();
        for (i=0;i<x_cl;i++)
         for (j=0;j<y_cl;j++)
         {
             for (o=0;o<x_cl;o++)
              for (p=0;p<y_cl;p++)
             if((i==o)&&(j==p))
              continue;
             if(e[o][p]>0)
              dedout[o][p]=(-out[i][j]*e[o][p]);
         }

        return dedout;

    }*/


    // ////////// Mean scire error function //////////

    // Derivation of error with respect to out put

    double weight_int()
    {
        double x=(rand()%weight_size) * sqrt(2.0/weight_size);;
        return x;
    }
    void init_weight()
    {
        //weight_size=125;
               uint16 i,j,k,m;

                   for( k=0;k<weight_size;k++)
                    {
                          weight[k]=weight_int();
                        //  cout<<weight[k];

                    }



    }
    double **mean_squre_error(double **t,double **out,uint16 x_cl,uint16 y_cl)
    {
        double **e=new double*[x_cl]();
        uint16 i,j;
        for( i=0;i<x_cl;i++)
        {
            e[i]=new double[y_cl]();
            for( j=0;j<y_cl;j++)
            e[i][j]=1/2*(t[i][j]-out[i][j])*(t[i][j]-out[i][j]);
        }
        return e;

    }

    void mean_test_squre_error(uint16 no_class)
    {
        uint16 x_cl=image_x,y_cl=image_y;

        double **r=new double*[x_cl]();
        double multi=x_cl*y_cl;
        uint16 i,j,k,temp_class=0;
        double e_r=9999,tm_err=0.0;
        for( i=0;i<x_cl;i++)
        {
            r[i]=new double[y_cl]();
            for( j=0;j<y_cl;j++)
            {

                for( k=1;k<=no_class;k++)
                {
                    tm_err=1/2*(k-output[i][j])*(k-output[i][j]);
                    if(tm_err<e_r)
                    {
                        e_r=tm_err;
                        temp_class=k;
                    }
                }
                output[i][j]=temp_class;
                avg=avg +e_r/multi;
            }

        }
       // return r;

    }

    double dirivation_error(double **t)
    {
        double dedout=0.0,multi=image_x*image_y;
        uint16 i,j,x_cl=image_x,y_cl=image_y;
//        cout<<x_cl<<"\t"<<y_cl;

        for( i=0;i<x_cl;i++)
        {
            //dedout[i]=new double[y_cl]();
            for( j=0;j<y_cl;j++)
            dedout=dedout+2*(output[i][j]-t[i][j]);
        }
       // cout<<dedout;

        //cout<<(dedout/multi);
        return (dedout/multi);

    }
    double percentage_of_mach_found(double **t)
    {
       // double **t=new double*[x_cl];
        uint16 x_cl=image_x, y_cl=image_y;
        uint32 sum=0,i,j;
        double result=0;

        for(i=0;i<x_cl;i++)
        {
           // t[i]=new double[y_cl];

            for(j=0;j<y_cl;j++)
            {
               // cout<<output[i][j]<<"\n";
                if(t[i][j]==output[i][j])
                {
                    sum=sum+1;
                  //  cout<<"Mach found";
                }

            }

        }
//        MPI_Allreduce(&sum,&sum,1,MPI_UNSIGNED,MPI_SUM, MPI_COMM_WORLD);
       result=sum/(x_cl*y_cl);
        return result;
    }
    double back_propagation(double ***input,double **t,uint16 no_neuran)
    {
        uint16 i,j,k,x_cl=image_x,y_cl=image_y;
        double total=0,sum=0,de=dirivation_error(t);

            for(j=0;j<x_cl;j++)
            {

                for(k=0;k<y_cl;k++)
                {
                total=0;
                    for(i=0;i<no_neuran;i++)
                {
                    //weight[j][k]-=input[i][j][k]*Lr*de;
                    total+=input[i][j][k];
                }
                    sum+=total;
                    //cout<<total*LR*de;
                    //cout<<total;
                  weight[j*y_cl+k]-=total*LR*de;
                  //cout<<weight[j*y_cl+k];
                }
            }
            return sum;
    }

    void fully_connection_layer(double ***input,uint16 no_neuran)
    {
        uint16 i,j,k,x_cl=image_x,y_cl=image_y;
        double total=0;

            for(j=0;j<x_cl;j++)
            {

                for(k=0;k<y_cl;k++)
                {
                   // output[j][k]=0;
                    total=0;
                    for(i=0;i<no_neuran;i++)
                {
                    total+=input[i][j][k];
                }
                  //  cout<<total;
                    output[j][k]=total*weight[j*y_cl+k];
                    //cout<<output[j][k];
                    //output[j][k]+=weight[weight_size-1];
                }
            }
    }
    serial_softmax_error(uint16 in_x,uint16 in_y)
    {
        weight=new double[in_x*in_y+1];
        output =new double*[in_x];
        weight_size=in_x*in_y+1;
        uint16 i=0;
        for(i=0;i<in_x;i++)
        {
            output[i]=new double[in_y];
        }
        image_x = in_x;image_y=in_y;
        init_weight();
    }


};
