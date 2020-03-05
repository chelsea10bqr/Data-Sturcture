/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T sum(stack<T>& s)
{
  if(s.empty()){
    return 0;
  }
   T a = s.top();
   s.pop();
   T su = a + sum(s);
   s.push(a);
   return su;

    // Your code here
     // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of
 * square bracket characters, [, ], and other characters. This function will return
 * true if and only if the square bracket characters in the given
 * string are balanced. For this to be true,
 * all brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is balanced,
 * "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is balanced.
 *
 * For this function, you may only create a single local variable of type stack<char>!
 * No other stack or queue local objects may be declared. Note that you may still
 * declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{  bool is = true;
  int pr = 0;
  stack<char> empty;
  if(input.empty()){
    return true;
  }
  while(!input.empty()){
    if (input.front() =='['&&pr>=0){
    pr=pr+1;
  }
    if(input.front()==']'){
     pr = pr-1;
    }
    input.pop();
    }
  if(pr!=0){
    return false;
  }
return true;

}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(queue<T>& q)
{   queue<T> temp;
    stack<T> s;
    int count = 1;
    while(!q.empty()){
      if(count%2==1){
        for(int i=1;i<=count;i++){
          T t = q.front();
          temp.push(t);
          q.pop();
          if(q.empty()){
            break;
          }
        }
        count++;
      }else if(count%2==0){
          for(int i =1;i<=count;i++){
            T t = q.front();
            s.push(t);
            q.pop();
            if(q.empty()){
              break;
            }
          }
          while(!s.empty()){
          T p = s.top();
          temp.push(p);
          s.pop();
         }
         count++;
        }
      }
      q = temp;
    }
    // optional: queue<T> q2;

    // Your code here


/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note The back of the queue corresponds to the top of the stack!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{  bool retval =true ;

    // Your code here
  while(s.empty()){
    return retval;
  }
    T  temps = s.top();
     s.pop();               /*pop the stack to empty*/
  retval=verifySame(s,q);
    if(temps!=q.front()){       /*and compare to q.front*/
      retval = false;
    }
    T temp1 = q.front();
     q.pop();                      /*move to the next element of queue*/
     q.push(temp1);
     s.push(temps);

    return retval;
 }

}
