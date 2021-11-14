package Src;

/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */

public class ListNode {
	      int val;
	     ListNode next;
	      ListNode() {}
	      ListNode(int val) { this.val = val; }
	      ListNode(int val, ListNode next) { this.val = val; this.next = next; }
	      
	      public static void main(String[] args ) {
	  		ListNode testOne = new ListNode(2);
	  		ListNode testTwo = new ListNode(-1);
	      	System.out.println(mergeTwoLists(testOne, null).val);
	      	System.out.println(mergeTwoLists(mergeTwoLists(testOne, null), testTwo).val);
	      }
	  	
	      public static ListNode mergeTwoLists(ListNode l1, ListNode l2) {
	          ListNode currentOne = l1;
	          ListNode currentTwo = l2;
	          ListNode result = new ListNode();
	          ListNode rootNode = result;
	          ListNode currentResult;	          
	          while(currentOne != null || currentTwo != null){
	              if(currentOne == null){
	                  currentResult = new ListNode(currentTwo.val);
	                  currentTwo = currentTwo.next;
	                  result.next = currentResult;
	                  result = result.next;
	              }
	              else if (currentTwo == null){
	                  currentResult = new ListNode(currentOne.val);
	                  currentOne = currentOne.next;
	                  result.next = currentResult;
	                  result = result.next;
	              }
	              else if(currentOne.val <= currentTwo.val){
	                  currentResult = new ListNode(currentOne.val);
	                  currentOne = currentOne.next;
	                  result.next = currentResult;
	                  result = result.next;
	              }
	              else{
	                  currentResult = new ListNode(currentTwo.val);
	                  currentTwo = currentTwo.next;
	                  result.next = currentResult;
	                  result = result.next;
	              }
	          }
	          if(rootNode.next != null){
	              rootNode = rootNode.next;
	          }
	          return rootNode;
	      }
	      
	      }