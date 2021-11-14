package Src;

public class RemoveDuplicate {
	public static int removeDuplicates(int[] nums) {
		if(nums.length == 0){
            return 0;
        }
        int length = 1;
        int check = nums[0];
        int tempNumber = 0;
        for(int i = 1; i < nums.length; i++){
            if(nums[i] == check){
                nums[i] = 9999;
            }
            else{
            	tempNumber = nums[i];
                check = nums[i];
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
    	int[] testCase = {1,2};
    	System.out.println(removeDuplicates(testCase));
    	for (int i = 0; i < testCase.length; i++){
            System.out.print(testCase[i] + " ");
        }
    }
}
