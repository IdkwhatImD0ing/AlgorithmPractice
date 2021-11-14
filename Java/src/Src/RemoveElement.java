package Src;

public class RemoveElement {
	public static int removeElement(int[] nums, int val) {
		if(nums.length == 0){
            return 0;
        }
		
        int length = 0;
        int check = val;
        int tempNumber = 0;
        for(int i = 0; i < nums.length; i++){
            if(nums[i] == check){
                nums[i] = 9999;
            }
            else{
            	tempNumber = nums[i];
                nums[i] = 9999;
                insertNumber(tempNumber, nums);
                length++;
            }
        }
        return length;
    }
    
    public static void insertNumber(int x, int[] nums){
        for (int i = 0; i < nums.length; i++){
            if(nums[i] == 9999){
                nums[i] = x;
                return;
            }
        }
    }
    
    public static void main(String[] args ) {
    	int[] testCase = {0,1,2,2,3,0,4,2};
    	System.out.println(removeElement(testCase,2));
    	for (int i = 0; i < testCase.length; i++){
            System.out.print(testCase[i] + " ");
        }
    }
}
