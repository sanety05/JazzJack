void BobbleSort(float array[ ],int n)
{
   int i, j, temp;

    for (i = 0; i < n - 1; i++) {
        for (j = n - 1; j > i; j--) {
            if (array[j - 1] > array[j]) { 
                temp = array[j];       
                array[j] = array[j - 1];
                array[j - 1]= temp;
            }
        }	
}
}
