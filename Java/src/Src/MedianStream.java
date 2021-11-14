package Src;



public class MedianStream {
    public static void main(String[] arg){
		int[] IntegerStream = {4,3,5,6,1,2,7,2};
        System.out.println(findMedian(IntegerStream));
        int[] IntegerStream2 = {4,2,3,5,1};
		System.out.println(findMedian(IntegerStream2));
    }

    public static double findMedian(int[] IntegerStream){
		MinHeap minHeap = new MinHeap(IntegerStream.length);
        MaxHeap maxHeap = new MaxHeap(IntegerStream.length);
        double median = IntegerStream[0];
        for(int i = 1; i < IntegerStream.length; i++){
			if(IntegerStream[i] < median){
                maxHeap.insert(IntegerStream[i]);
            }
            else{
                minHeap.insert(IntegerStream[i]);
            }
            if(maxHeap.size() > minHeap.size()){
                median = maxHeap.extractMax();
            }
            else if(maxHeap.size() < minHeap.size()){
                median = minHeap.extractMin();
            }
            else{
                median = (minHeap.extractMin() + maxHeap.size())/2.0;
            }
        }

        maxHeap.print();
        minHeap.print();

        return median;
    }
}
