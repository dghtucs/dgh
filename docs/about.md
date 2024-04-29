# 清华

[网络学堂](https://learn.tsinghua.edu.cn/f/wlxt/index/course/student/)

[清华info](https://info2021.tsinghua.edu.cn/f/info/gxfw_fg/common/index)

[清华邮箱](https://mails.tsinghua.edu.cn/coremail/XT/index.jsp?sid=EAGuaeXXdXichLsOLyahhjZvOZAGmTnK#mail.list%7C%7B%22fid%22%3A1%7D)



# 计算机

[github](https://github.com/dghtucs)


# 数学




# 技能





# 知识
Comments serve as a sort of in-code documentation. When inserted into a program, they are effectively ignored by the compiler; they are solely intended to be used as notes by the humans that read source code.

Syntax
/* comment */	(1)	
// comment	(2)	(since C99)
1) Often known as "C-style" or "multi-line" comments.
2) Often known as "C++-style" or "single-line" comments.
All comments are removed from the program at translation phase 3 by replacing each comment with a single whitespace character.

C-style
C-style comments are usually used to comment large blocks of text or small fragments of code; however, they can be used to comment single lines. To insert text as a C-style comment, simply surround the text with /* and */. C-style comments tell the compiler to ignore all content between /* and */. Although it is not part of the C standard, /** and **/ are often used to indicate documentation blocks; this is legal because the second asterisk is simply treated as part of the comment.

Except within a character constant, a string literal, or a comment, the characters /* introduce a comment. The contents of such a comment are examined only to identify multibyte characters and to find the characters */ that terminate the comment. C-style comments cannot be nested.

C++-style
C++-style comments are usually used to comment single lines of text or code; however, they can be placed together to form multi-line comments. To insert text as a C++-style comment, simply precede the text with // and follow the text with the new line character. C++-style comments tell the compiler to ignore all content between // and a new line.

Except within a character constant, a string literal, or a comment, the characters // introduce a comment that includes all multibyte characters up to, but not including, the next new-line character. The contents of such a comment are examined only to identify multibyte characters and to find the new-line character that terminates the comment. C++-style comments can be nested:

//  y = f(x);   // invoke algorithm
A C-style comment may appear within a C++-style comment:

//  y = f(x);   /* invoke algorithm */
A C++-style comment may appear within a C-style comment; this is a mechanism for excluding a small block of source code:

/*
    y = f(x);   // invoke algorithms
    z = g(x);
*/
(since C99)
Notes
Because comments are removed before the preprocessor stage, a macro cannot be used to form a comment and an unterminated C-style comment doesn't spill over from an #include'd file.

/* An attempt to use a macro to form a comment. */
/* But, a space replaces characters "//".       */
#ifndef DEBUG
    #define PRINTF //
#else
    #define PRINTF printf
#endif
...  
PRINTF("Error in file %s at line %i\n", __FILE__, __LINE__);
Besides commenting out, other mec