
float neural_network_testing(opt_convolutional_network **p,\
                               opt_deconvolutional_network **dp,\
                               serial_softmax_error *s,\
                               uint16 layer,\
                               char layers[],\
                               double** image,\
                               uint16 image_x,
                               uint16 image_y,\
                               double** test_array)
{



    float gradiant=1.0;int i,j,k=0,p_no=0,l;
    uint16 im_x=image_x,im_y=image_y;
    int *****position=new int****[NO_POOLING_LAYERS];

    for( i=0;i<layer;i++)
           {
                switch(layers[i])
                {
                case 'C':
              if(i==0)
                {
                   p[k]->convolutional_layer_pool(image,true);
                   im_x-=WEIGHT_ROW;
                   im_y-=WEIGHT_COLUMN;
                  //  p[i]->frowork_oparation();
                  // k++;
                    //continue;

                }
              else
                for(j=0;j<NO_NEURAN;j++)
                {

                  p[k]->convolutional_layer_pool(p[k-1]->output[j],true);
                  im_x-=WEIGHT_ROW;
                  im_y-=WEIGHT_COLUMN;

                 //   p[i]->frowork_oparation();
                }
                k++;
                //cout<<"In conbv"<<"\n";
                break;
                case 'P':
              if(i==0)
                {
                   p[k]->convolutional_layer_pool(image,true);
                   im_x-=WEIGHT_ROW;
                   im_y-=WEIGHT_COLUMN;
                  //  p[i]->frowork_oparation();
                  // k++;
                    //continue;

                }
              else
                for(j=0;j<NO_NEURAN;j++)
                {

                  p[k]->convolutional_layer_pool(p[k-1]->output[j],true);
                  im_x-=WEIGHT_ROW;
                  im_y-=WEIGHT_COLUMN;

                 //   p[i]->frowork_oparation();
                }
                k++;
                //cout<<"In conbv"<<"\n";
                break;
                //continue;
                case 'D':
                    if(k==NO_CONVOLUTION_LAYERS)
                        dp[k-1]->input=p[k-1]->output;
                    else
                        dp[k-1]->input=dp[k]->output;
                     dp[k-1]->deconvolutional_layer(true);
                    k--;
                 break;
                case 'U':
                    if(k==NO_CONVOLUTION_LAYERS)
                       dp[k-1]->input=p[k-1]->output;
                    else
                        dp[k-1]->input=dp[k]->output;
                    dp[k-1]->deconvolutional_layer(true);
                        k--;
                break;

                }


            }

            s->fully_connection_layer(dp[0]->output,NO_NEURAN);
            s->mean_test_squre_error(NO_NEURAN);
            double r=s->percentage_of_mach_found(test_array);
            return r;


}

void neural_network_training(opt_convolutional_network **p,\
                             opt_deconvolutional_network **dp,\
                             serial_softmax_error *s,\
                             uint16 layer,\
                             char layers[],\
                             double** image,\
                             uint16 image_x,
                             uint16 image_y,\
                             double** train_array)
{

double gradiant=0.0;int i,j,k=0,c_no=-1,d_no=-1,l;
uint16 im_x=image_x,im_y=image_y;

int *****position=new int****[NO_POOLING_LAYERS];

for( i=0;i<layer;i++)
        {


    if(layers[i]=='C'||layers[i]=='P')
    {

        if(i==0)
          p[k]->convolutional_layer_pool(image,false);
        else
          for(j=0;j<NO_NEURAN;j++)
          {

            p[k]->convolutional_layer_pool(p[k-1]->output[j],false);
            im_x-=WEIGHT_ROW;
            im_y-=WEIGHT_COLUMN;

           //   p[i]->frowork_oparation();
          }

        k++;
        c_no++;
        //cout<<k<<"in convo \t"<<c_no;

    }
    else
    {


        if(k==NO_CONVOLUTION_LAYERS)
           dp[k-1]->input=p[k-1]->output;
        else  dp[k-1]->input=dp[k]->output;
        if(layers[i]=='U')
        {
            dp[k-1]->position=p[k-1]->position;

        }

        dp[k-1]->deconvolutional_layer(false);

        k--;
        //cout<<k<<"\t in dconvo"<<c_no;
        d_no++;


    }

    if(i==0) continue;
    else if(d_no>=0)
    {
        gradiant=dp[k]->gradent_sum;
        for(j=k;j<NO_CONVOLUTION_LAYERS;j++)
            dp[j]->persial_training(gradiant);
        for(j=c_no;j>=0;j--)
            p[j]->persial_training(gradiant);
    }
    else
    {
        gradiant=p[c_no]->gradent_sum;
        for(j=c_no;j>=0;j--)
            p[j]->persial_training(gradiant);
    }
}


        s->fully_connection_layer(dp[0]->output,NO_NEURAN);
      //  double de= s->dirivation_error(train_array);
        double de=s->back_propagation(dp[0]->output,train_array,NO_NEURAN);

        //double de=s.dirivation_error(train_array,dp[NO_CONVOLUTION_LAYERS-1]->output[0],image_x,image_y);
        for(j=0;j<NO_CONVOLUTION_LAYERS;j++)
        {
           //for(l=0;l<12;l++)
           //de=p[j]->back_propagation(de,p[j-1]->output[l]);
           dp[j]->back_propagation(de);
           //cout<<de<<"\n";
        }
       // de=p[NO_CONVOLUTION_LAYERS-1]->back_propagation(de,p[NO_CONVOLUTION_LAYERS-2]->output[l]);


        for(j=NO_CONVOLUTION_LAYERS-1;j>=1;j--)
        {
           //for(l=0;l<12;l++)
           //de=p[j]->back_propagation(de,p[j-1]->output[l]);

          p[j]->back_propagation(de);
           //cout<<de<<"\n";
        }
        p[j]->back_propagation(de);


}
