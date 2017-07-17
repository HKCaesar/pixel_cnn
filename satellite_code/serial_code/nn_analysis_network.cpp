
float neural_network_testing(convolutional_network **p,\
                               deconvolutional_network **dp,\
                               serial_softmax_error *s,\
                               uint16 layer,\
                               char layers[],\
                               double** image,\
                               uint16 image_x,
                               uint16 image_y,\
                               double** test_array)
{
    /*

    float gradiant=1.0;int i,j,k=0,p_no=0,l;
    uint16 im_x=image_x,im_y=image_y;
    int *****position=new int****[NO_POOLING_LAYERS];
    /*
    for( i=0;i<layer;i++)
            {

                if(i==0)
                {
                    p[i]->convolutional_layer(image);
                    //p[i]->frowork_oparation();
                    continue;
                }
                for(j=0;j<feture[i-1];j++)
                {
                    p[i]->convolutional_layer(p[i-1]->output[j]);
                    //p[i]->frowork_oparation();
                }
            }
    for( i=0;i<layer;i++)
            {


                switch(layers[i])
                {
                case 'C':
                    if(i==0)
                    {
                       p[k]->convolutional_layer(image);
                       im_x-=WEIGHT_ROW;
                       im_y-=WEIGHT_COLUMN;
                      //  p[i]->frowork_oparation();
                       //k++;
                       // continue;
                    }
                    else
                for(j=0;j<NO_NEURAN;j++)
                {

                  p[k]->convolutional_layer(p[k-1]->output[j]);
                  im_x-=WEIGHT_ROW;
                  im_y-=WEIGHT_COLUMN;

                 //   p[i]->frowork_oparation();
                }
                k++;
                break;
                case 'P':
                position[p_no]=p[k-1]->pooling();
                p_no++;
                continue;
                case 'D':
                if(k==NO_CONVOLUTION_LAYERS)
                    dp[k-1]->input=p[k-1]->output;
                else
                    dp[k-1]->input=dp[k]->output;
                dp[k-1]->deconvolutional_layer();
                k--;
                continue;
                case 'U':
                dp[k-1]->uppooling(position[p_no-1]);
                p_no--;
                continue;

                }

               // for(j=i;j>=0;j--)
               // {
                //    gradiant=p[j]->partial_training(gradiant);
    //           / }

            }
            //serial_softmax_error s;
            s->fully_connection_layer(dp[NO_CONVOLUTION_LAYERS-1]->output,NO_NEURAN);
            //double de=s->back_propagation(dp[NO_CONVOLUTION_LAYERS-1]->output,train_array,12);
            //double de=s.dirivation_error(train_array,dp[NO_CONVOLUTION_LAYERS-1]->output[0],image_x,image_y);
            double **result=s->mean_test_squre_error(NO_NEURAN);
            */
            //double r=0;//s->percentage_of_mach_found(result);
            //return r;

   // softmax_error s;
   // float** test_result=s.mean_test_squre_error(p[layer-1]->output[0],image_x,image_y,no_class);

   // return test_result;


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
                   p[k]->convolutional_layer(image);
                   im_x-=WEIGHT_ROW;
                   im_y-=WEIGHT_COLUMN;
                  //  p[i]->frowork_oparation();
                  // k++;
                    //continue;

                }
              else
                for(j=0;j<NO_NEURAN;j++)
                {

                  p[k]->convolutional_layer(p[k-1]->output[j]);
                  im_x-=WEIGHT_ROW;
                  im_y-=WEIGHT_COLUMN;

                 //   p[i]->frowork_oparation();
                }
                k++;
                //cout<<"In conbv"<<"\n";
                break;
                //continue;

                case 'P':
                  //  cout<<k;
                position[p_no]=p[k-1]->pooling();
                p_no++;

                break;


                case 'D':

                    if(layers[i-1]!='U')
                        dp[k-1]->input=dp[k]->output;
                     dp[k-1]->deconvolutional_layer();
                    k--;
                 break;
                case 'U':
                    if(k==NO_CONVOLUTION_LAYERS)
                       dp[k-1]->input=p[k-1]->output;
                    else
                        dp[k-1]->input=dp[k]->output;
                dp[k-1]->uppooling(position[p_no-1]);
                p_no--;

                break;

                }


            }

            s->fully_connection_layer(dp[0]->output,NO_NEURAN);
            double **result=s->mean_test_squre_error(NO_NEURAN);
            double r=s->percentage_of_mach_found(result);
            return r;


}

void neural_network_training(convolutional_network **p,\
                             deconvolutional_network **dp,\
                             serial_softmax_error *s,\
                             uint16 layer,\
                             char layers[],\
                             double** image,\
                             uint16 image_x,
                             uint16 image_y,\
                             double** train_array)
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
               p[k]->convolutional_layer(image);
               im_x-=WEIGHT_ROW;
               im_y-=WEIGHT_COLUMN;
              //  p[i]->frowork_oparation();
              // k++;
                //continue;

            }
          else
            for(j=0;j<NO_NEURAN;j++)
            {

              p[k]->convolutional_layer(p[k-1]->output[j]);
              im_x-=WEIGHT_ROW;
              im_y-=WEIGHT_COLUMN;

             //   p[i]->frowork_oparation();
            }
            k++;
            //cout<<"In conbv"<<"\n";
            break;
            //continue;
            case 'P':
              //  cout<<k;
            position[p_no]=p[k-1]->pooling();
            p_no++;
            //cout<<"In pool"<<"\n";
            //return;
            break;
            //continue;

            case 'D':
          //  cout<<"In D";
            //if(k==NO_CONVOLUTION_LAYERS)
             //   dp[k-1]->input=p[k-1]->output;
            //else
                //if(k!=NO_CONVOLUTION_LAYERS)
                //dp[k-1]->input=dp[k]->output;
             //   dp[k-1]->deconvolutional_layer();
                if(layers[i-1]!='U')
                    dp[k-1]->input=dp[k]->output;
                dp[k-1]->deconvolutional_layer();
                k--;
             break;
            case 'U':
                if(k==NO_CONVOLUTION_LAYERS)
                   dp[k-1]->input=p[k-1]->output;
                else
                    dp[k-1]->input=dp[k]->output;
            dp[k-1]->uppooling(position[p_no-1]);
            p_no--;
           // cout<<"In U";
            break;

            }


           // for(j=i;j>=0;j--)
           // {
            //    gradiant=p[j]->partial_training(gradiant);
//           / }

        }
        //serial_softmax_error s;
        //cout<<dp[0]->x_output;
        s->fully_connection_layer(dp[0]->output,NO_NEURAN);
        double de= s->dirivation_error(train_array);
        //double de=s->back_propagation(dp[0]->output,train_array,NO_NEURAN);

        //double de=s.dirivation_error(train_array,dp[NO_CONVOLUTION_LAYERS-1]->output[0],image_x,image_y);
        for(j=0;j<NO_CONVOLUTION_LAYERS;j++)
        {
           //for(l=0;l<12;l++)
           //de=p[j]->back_propagation(de,p[j-1]->output[l]);
           de=dp[j]->back_propagation(de);
           //cout<<de<<"\n";
        }
       // de=p[NO_CONVOLUTION_LAYERS-1]->back_propagation(de,p[NO_CONVOLUTION_LAYERS-2]->output[l]);


        for(j=NO_CONVOLUTION_LAYERS-1;j>=1;j--)
        {
           //for(l=0;l<12;l++)
           //de=p[j]->back_propagation(de,p[j-1]->output[l]);
            for(i=0;i<NO_NEURAN;i++)
           de=p[j]->back_propagation(de,p[j-1]->output[l]);
           //cout<<de<<"\n";
        }
        de=p[j]->back_propagation(de,image);


}
