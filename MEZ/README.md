
# MEZ – An easier language for learning programming.

MEZ is a programming language designed to be easier to use than C.
It can be used in command line or with the ‘.exe’ file included.
It is built with C language.
#### Video Demo:  <https://youtube/x-hItnyfEqM>
#### Description: The main aim of our proposed language is to make a programming language based on C that would be very easy to learn the basic principles of programming, such as assigning variables, making inputs and outputs for the user, and control flows. The language does this without being too verbose, allowing a person with minimal programming language experience, may it be old folks or young kids with little computer literacy, to actually be able to write code in a manner that most reflects what actual programmers do.
Most programming languages that do this (such as MIT’s Scratch or the open source Emojicode) accomplish this by making the interface as user friendly as possible, but for us the act of “writing code” should also be a given feel in teaching programming. The idea of sitting down in front of a screen, writing and debugging code in a language you are just starting to learn can seem like a tall order. By using our language, it would make the daunting task to some, a more manageable and easier to learn format that can be picked up by all, allowing users to focus on learning the concepts behind programming and developing the mindset of problem solving needed for a programmer.
The language was inspired by the fact that there are currently no easy ways or shortcuts in learning programming. We endeavour to create a programming language that would make everything in a symbolic, easy to categorise, and recognizable format. Allowing the use of purely symbolic code with the most basic usages be explained as simply as possible, even if the other users don’t have the same linguistic acuity as you.


## Character Set

```
MEZ= {LETTERS,DIGITS,SYMBOLS}
LETTERS={CAP,SM}
CAP={A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z}
SM= {a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z}
DIGITS= {0,1,2,3,4,5,6,7,8,9}
SYMBOLS={ARITHMETIC,!,",#,$,&,', (,),,,.,:,;,<,=,>,?,@,[,\,],_,`,{,|,},~}
ARITHMETIC={+,-,*,/,%,^}
BOOL={<,>,==,<=,>=,&&,!=,||,!}
Identifiers:
1. Identifiers can only contain alphanumeric characters (a-z, A-Z, 0-9) and underscores(_).
2. The first letter of an identifier must be a letter(a-z,A-Z).
3. Keywords cannot be used as an identifier.
4. Identifiers are case sensitive.
Regular Expressions
    Set of strings that starts with a character from the set LETTERS that may or may not be followed by a combination of characters from set LETTERS, set DIGITS, and underscores.
IDENTIFIERS=LETTERS(LETTERS|DIGITS|_)*

```

## Features

- Lexical analysis with the output ‘Symbol Table.mez’
- Syntactical analysis with the output ‘outout.txt’
- Semantic analysis with the output in the command line by running the exe file
- ~~Interpretation of code through C~~


## Usage/Examples
Create an ‘input.mez’ file at the same directory and run the exe file.
The example program written in MEZ is provided below:
```
~<PPL Final Project>~
signed Str a = 'd' ;
Num b = "wrong" ;
unsigned Num re [ 3 ] , one ;
Num b , c ;
register Str lool ;
Str nonsense ;
auto Num nu ;

re = { 23 , 4 , 11 } ;
c = 2 - 3 ;
c = "mismatch" ;
no = 3.33 ;

scan ( Str , lool ) ;
scan ( Str , notha ) ;

if( a != false ) {
    print ( "loop" + b ) ;
}

if( nope > 2 ) {
    print ( "pool" + nana ) ;
} else if ( b <= 3 ){
    scan ( Num , nonsense ) ;
}

c = ( 4 * 2 ) / ( 10 % 3 ) ;

for ( i = 1 ; ( b < 1 ) || ( b > 4 ) ; b = b + "b" ) {

    break + 1;
}

S@dboi >= ( true // null ) ^ 2 && auto ! a == ;
```


## Lessons Learned

This project has honed my skills not just in programming, but in fostering a deeper understanding of how programming languages work.

## Authors

- [@King Red Sanchez]( https://github.com/haringpula)
- [@James Marck Maranon](https://github.com/Kytiex)
- [@Briel Aldous Viola]()
- [@John Elway Cortez]( https://github.com/Evrouin)


## Feedback

If you have any feedback, please reach out to me at kingredpula31@gmail.com

