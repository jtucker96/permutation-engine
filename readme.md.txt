11/12/2013	James Tucker	<mail@jamestucker.com>

Basic program skeleton created, confirmed working, currently loads all template files successfully and puts output in output file in orderly fashion. ",\" is also checked for, a common error if file is assembled - and removed to allow assembling output file to take place. Also "\n" is added to the end of each line so the file can be read by the assembler.

TODO:	Put in place a global register synchronising function to alter members of the structure of registers to true or false, indicating whether the register can be used by the JUNK GENERATOR, or not.

12/12/2013	James Tucker	<mail@jamestucker.com>

Fully implemented register selector, will only select a valid register/ a register that is not currently in use by main program. 

TODO: Create a method in which a [opcode blockobject] can be indexed and referenced through the RNG, so a random opcode can be selected from the list, which which a register can be created.
Also don't just use 32-bit registers for checking, redo it back to 8-bit support.

Currently errors when :
[Reg index = 3 & Reg type = 1] && [Reg index = 3 & Reg Type = 2] (When condition is applied)
FIXED : Addition index problem.

12/12/2013	James Tucker	<mail@jamestucker.com>

Corrected class error across multiple CPP files. Added a string pointer array to reference each member of a single vector
	string * m_szVectorIndexingArr[16];// = new string[48];
	for (unsigned int i = 0; i < m_opcodeAdding.m_vszBuffer.size(); i++)
	{
		m_szVectorIndexingArr[i] = &m_opcodeAdding.m_vszBuffer[i];
		cout << *m_szVectorIndexingArr[i];
	}
TODO: Make an array of these (container) so one can be randomly generated, hence opcode generated.

12/12/2013	James Tucker	<mail@jamestucker.com>

Changed how classes were initialized, classes are now initialized through arrays therefore they can easily be looped through. Encountered a problem with the opcode generator in terms of memory allocation, however it is fixed. Currently the program can generate a random opcode. With correct index?

TODO: Intelligence with the opcode, make the calls to RNG not hardcoded, fix cleanup (currently causing violation bug)


13/12/2013	James Tucker	<mail@jamestucker.com>

Had to work on someones C++ final paper, used std::list through custom class member, so development didn't occur as normal. 
TODO: Going to completely rewrite it so I am working with std::list instead of 2d arrays.

13/12/2013	James Tucker	<mail@jamestucker.com>

Completely re-written the opcode generator to work with global std::list containing vectors
TODO: apply this to the register generator as well! EDIT : No real need to change the register generator UNLESS program encounters errors.

13/12/2013	James Tucker	<mail@jamestucker.com>

Encountered problem with register array string, because I had not modified that code in a while. Simple fix just create a static array in header file and source file instead of allocating on the heap.
TODO: Identify instructions and give them intelligence, ie. mov was selected with only one register, chance of generating another register of reg_size or use a variable as the source?


13/12/2013	James Tucker	<mail@jamestucker.com>

Structured main() a bit better, created process() function as a loopengine which I can fully implement later.
TODO: Add AI to the generated opcodes + generated registers!


13/12/2013	James Tucker	<mail@jamestucker.com>

Created a new cpp file, LookupTable, which will handle all AI!
TODO: Instead of focusing on AI, focus on the template, make sure the output is correct! Then AI will come!

13/12/2013	James Tucker	<mail@jamestucker.com>

Don't just use JMP to jump to trash code, rather use call, main difference is that you need to generate a new label to place in code after the jmp to trash, then call that label as a jmp to restore execution!
Added a new variable, g_uiLevelsIntoTrash, how many levels INSIDE trash are we? For example, normal running code for runPE is level = 0, when trash procedure is called - level will = 1, if trash is called INSIDE that trash procedure, ie another jmp, then level will = 2. This variable will be used as a check to make sure execution will be restored correctly!

TODO: As stated above

14/12/2013	James Tucker	<mail@jamestucker.com>

Just re-ordered resource.h to make it more readable, however am extremely tired so need rest!

15/12/2013	James Tucker	<mail@jamestucker.com>

Changed alot of the program, added a lookup table function to pinpoint which opcode is being used
Opcode generated -> THEN register, as all registers don't work with some opcodes
TODO: When opcode is generated, identify the minimum format required for that opcode to actually work, .. ie mov can be used as 
- source operand can be an immediate value, general-purpose register, segment register, or memory location, 
- destination register can be a general-purpose register, segment register, or memory location

15/12/2013	James Tucker	<mail@jamestucker.com>

TODO: When an opcode is generated, identify which section from the vector of opcodes is MOST LIKELY to be used next, and generate a random number from this usage, this will reduce entropy as junk is "SLIGHTLY" more predictable, thus less likely to pick up detections. 
To do this, a new global structure of individual structures shall be created, the structures which make up the overall structure shall have a minimum and maximum range for where RNG should pick for next opcode and a boolean value of if we should actually use that structure?

15/12/2013	James Tucker	<mail@jamestucker.com>

Thought - generate the opcode in the trashgen.cpp, however, leave all the formatting to lookuptable, including handling the generation of register, whether it will generate a register or immediate memory ect..

15/12/2013	James Tucker	<mail@jamestucker.com>

Completed the register generator aspect of the lookuptable and trashgen, however now comes time to implement a global structure of variables generated at runtime, with critical variables (used by actual program) in a different structure to the optional variables ONLY used by trash code, program will always check the critical variables which are not in use, select which one and use it! If not then use optional variable.
TODO: variable generation!

-	 	CHANGELOG DID NOT SAVE ON THIS DAY

17/12/2013	James Tucker	<mail@jamestucker.com>

Created first legitimate output with the program in console window using PROCEDURE, JMP, and DIRECT INSERT. Was successfull.
TODO: Fix up the problem where I cannot access the global lists from engine.cpp.
Also, add in CORRECT definitions for all operations in the table, so correct outputs can be generated!
EDIT : Also add support for memory!

17/12/2013	James Tucker	<mail@jamestucker.com>

Fixed the problem where I could not access lists ect.. Also fixed stupid fucking problem where two different sized registers were generated even though that was incorrect.
TODO: The fucking memory with variables

18/12/2013	James Tucker	<mail@jamestucker.com>

Fixed the stupid fucking register problem where two of the same registers couldn't be generated in the same operation code, 

18/12/2013	James Tucker	<mail@jamestucker.com>
Will fix up the issue where a register cannot be generated in source, as it doesn't matter if source register is used - FIXED, also reformatted source
TODO: now solely focus on memory, then on managing jumps!


18/12/2013	James Tucker	<mail@jamestucker.com>
Implemented memory generation
TODO: When m_uiMemIndex generates 1, the program halts and fails. I need to fix this.
Fixed, problem occurred within generatevariable.cpp when global iterator is decremented.
TODO : Add in boolean value which determines whether the register HAS TO BE same size as source, also fixup rotate bit shift number as a 0 was generated!

19/12/2013	James Tucker	<mail@jamestucker.com>
0 is generated as memory is generated, and the index value which is checked is not set, therefore only producing a range of 1,0, this will be fixed when I implement variable sizing as such.
Fixed global vector, now it can write to the output file everything generated.
TODO: Implement variable sizing  ,  make sure every single operand is valid,  then implement API calls.

20/12/2013	James Tucker	<mail@jamestucker.com>

Tidied up useless fucking code, made program more efficient in anticipation of extra features, ie sized calls to memory ect.. Fixed up more bugs that were made in editing the program such as LEA not having a second operand

current errors with : add, mov, sbb, xadd, cmp, sub
FIXED FOR those who call 8 for second operand : 
Problem is either two square brackets OR no second source operand to compliment

Now only : mov, sbb, sub - problem arises as program calls two brackets

Fixed up error, however this is only cause for more error as variables declared as dw or db cannot be used as 
mov [var], var2 or an out of range error occurs, dd works fine.

All fixed, now we need to fix up return jmps

21/12/2013	James Tucker	<mail@jamestucker.com>

Source compiles perfect, however errors did arise which were fixed, they included popping too many dwords from stack, and calling STI CLI which require higher permission.
TODO: Be able to randomly call procedures from within code that is directly inserted using valid arguments if applicable
JMPS can be achieved later when blocks are given purpose and that purpose is achieved ect..

Change of plan, generate all the procedures AND jumps at the beginning of the program! Later generate the direct insert.
Perfection. STDCALLS are successfully implemented in the program, however I have a funny feeling that they will fail with the memory being dereferenced ect..
As I was expecting, if the operand is dereferenced, then the size of the operand MUST be put in place in front of it
22/12/2013	James Tucker	<mail@jamestucker.com>
Found out what was fucking up the dereferencing, it was the internal list variable being updated with the brackets

Program fucks up with popa in a function, and push 16-bit value, just completely fucks up, so tip for future, don't use push with 16 bit value only 32 bit.
HOWEVER, push 16 bit value can be achieved if ANOTHER push 16 bit value compliments it! I think I may implement that later

Finally found a huge bug in my program, not enough parameters are pushed onto the stack before a call is made to SOME procedures, for example a procedure of prototype:
proc ITHINZ , arg1, arg2, arg3, arg4, arg5
Was only getting 2 arguments passed to it!

22/12/2013	James Tucker	<mail@jamestucker.com>

Output program is struggling with a recursion loop, where either the function is calling itself, or a function is calling a function which is calling that specified function, therefore completely fucking up. First solution is to prevent a function from calling itelf..


23/12/2013	James Tucker	<mail@jamestucker.com>


Changelog.txt did not save for updated work on the 22nd. Currently in the process of fixing up the recursive calls which deadlocks the program. Right now the program searches a procedure for a stdcall label and extracts that label, now it must search the current procedure label vector for that matching label and do the check inside that procedure for any stdcalls it shouldnt have.
				string m_szLabel = m_lsTempIter->m_vszBuffer[i].substr(8,(m_lsTempIter->m_vszBuffer[i].find(","))-8);


24/12/2013	James Tucker	<mail@jamestucker.com>

Sickness has affected development time drastically, however I am continuing. My current implementation of preventing the program from locking in a seemingly recursive loop is only a rough outline of what is possible. To drastically simplify things, I can make a vector string in each procedure TRASHOBJ of the stdcalls a procedure makes, this is definitely a good idea in preventing the program from breaking.
Newest update will drastically improve performance, as the ENTIRE procedure buffer is not searched UNLESS there is a genuine match


25/12/2013	James Tucker	<mail@jamestucker.com>

Completely fixed the program, STD and CLD were contributing to the program breaking, as well as POPF afaik.
TODO: Generate random API calls, first get a massive list

05/01/2014	James Tucker	<mail@jamestucker.com>

I am back from developing other programs for other people, and am now currently attempting to figure out what to do next. I think it was implementing win32 API calls, and mimicing legitimate programs like notepad.exe, matching their API calls
 > http://security.stackexchange.com/questions/30362/how-do-antiviruses-scan-for-thousands-of-malware-signatures-in-a-short-time



Possible permutations
1 - 
Extract data into buffer      
Extract path into buffer      
Decrypt buffer to valid data   
Decrypt buffer to valid path
2 - 
Extract path into buffer
Decrypt buffer to valid path
Extract data into buffer
Decrypt buffer to valid data
3 -
Extract data into buffer
Extract path into buffer
Decrypt buffer to valid path
Decrypt buffer to valid data
4 -
Extract data into buffer
Decrypt buffer to valid data
Extract path into buffer
Decrypt buffer to valid path

To add more permutations, add more operations,
For example locating decryption key which is stored in the file..

Each individual instructions above make up a set, in order for the set to be complete all individual instructions inside the set must be complete, ie boolean to true - for this, global structure will exist with individual structures inside.

