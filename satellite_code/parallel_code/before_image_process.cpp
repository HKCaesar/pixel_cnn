



void serial_image_preprocessing(string image_name,read_write  **&images,double  ***&temp_images)
{

    uint32 i,j, x=0;
    static bool first=true;
    if(first)
    images=new read_write*[NO_IMAGES_PARTS];
    if(first)
    temp_images=new double**[NO_IMAGES_PARTS];
     //images[0]=new read_write("6040_1_3",SWIR_X,SWIR_Y,0,0);
     //images[1]=new read_write("6040_1_3",SWIR_X,SWIR_Y,0,Y_PART);
//#pragma omp parallel for  firstprivate(x) private(j)

    for(i=0;i<IMAGE_X_SIZE;i+=X_PART)
        for(j=0;j<IMAGE_Y_SIZE;j+=Y_PART)
     {

//            cout<<x<<" "<<image_name<<" "<<SWIR_X<<" "<<SWIR_Y<<" "<<i<<" "<<j<<"\n";
        //    #pragma omp critical

          //uint32  x=(i/X_PART+j/Y_PART);

            if(first)
              {
                images[x]=new read_write(image_name,SWIR_X,SWIR_Y,i,j);
            }
            else
                images[x]->reset(image_name,SWIR_X,SWIR_Y,i,j);

         serial_image_matrix nir1(images[x]->image_M[6],M_IMAGE_X,M_IMAGE_Y);
         serial_image_matrix r(images[x]->image_3[0],RGB_IMAGE_X,RGB_IMAGE_Y);
         serial_image_matrix g(images[x]->image_3[1],RGB_IMAGE_X,RGB_IMAGE_Y);
         serial_image_matrix b(images[x]->image_3[2],RGB_IMAGE_X,RGB_IMAGE_Y);
         //uint16 image_x=250,image_y=250;
         nir1.matrix_size_incr(RGB_IMAGE_X,RGB_IMAGE_Y);
         serial_image_matrix nir11(nir1.matrix_scale_up(0.1),RGB_IMAGE_X,RGB_IMAGE_Y);
         serial_image_matrix nir12(nir1.matrix_scale_up(0.3),RGB_IMAGE_X,RGB_IMAGE_Y);
         serial_image_matrix nir13(nir1.matrix_scale_up(0.2),RGB_IMAGE_X,RGB_IMAGE_Y);
         serial_image_matrix temp=(nir12+nir13);
         temp=(temp+nir11);
         temp_images[x] = temp.p;
         x++;

     }
    first=false;
    //cout<<x;*/

}




