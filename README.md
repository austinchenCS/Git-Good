# "Git -Good" C/C++ Static Code Analyzer


This report document explains the metrics, scoring, code architecture, and annotated reports of our "Git -Good" C/C++ Static Code Analyzer. In addition, we have a "leaderboard" of code scores for various codebases (such as Swift, 7zip, Git -Good itself, etc.) at the bottom of the document.

## Metrics

Our C/C++ Code Analyzer scans one’s codebase for five total categories of metrics. 

Though our Static Code Analyzer tracks dozens of smaller component metrics, we decided to group each metric into broader subcategories. These categories are Line Metrics, Comment Metrics, Variable Metrics, Class Metrics, and Halstead Metrics. Creating broader categories provides structure and organization to the output report, and enhances readability for the user. Furthermore, from our own programmer’s perspective, we can continue adding smaller component metrics its best-fit parent category. For example, in this current version of our program, the only metric that our “Variable Metrics” class tracks is average variable length for primitive data types. If we wanted to add the metric of “variable name quality” in the future, we could simply add the metric to the larger parent class of “Variable Metrics”, and not disrupt the overall organization of our class hierarchy. If, in the future, we add a metric that is unrelated to any of the five parent categories, we can always create a new parent metric class.


Our decision to group smaller metrics into parent categories also plays a significant role in how the user’s program is scored. For each file in the analyzed directory, the user receives a score for each metric category (see the annotated outputs below). When the user is quickly scrolling through the output, they will be able to quickly see each category’s score. We believe that reading a short output:
```
FILE SCORE: 56
Line Metrics Score: 40
Variable Metrics Score: 16
Class Metrics Score: 0
Comment Metrics Score: 5
Halstead Metrics Score: 12
```

...would be much more meaningful than reading an output like this:

```
Inlined Comment Score: 3
Number of lines Score: 5
Program Vocabulary Score: 9
Class Naming Convention Score: 8
Ratio of Comments Score: 12
Expected Time Score: 12
Lines with C/C++ Instruction Score: 3
Program Volume Score: 2
Lines That Spill Over 80 Score: 13
…etc.
```

We believe the latter example has no clear organization and is much more difficult to digest, upon first glance.


Let’s dive deeper into each of the five metric categories...


### Line Metrics:
As per the title, the line metrics parent category aggregates every metric that relates to lines. Our Line Metrics category contains:

* Total number of lines in the file
* Number of lines with C/C++ instruction
* Number of whitespace lines in file
* Ratio of comment lines to total lines of C/C++ instruction
* Ratio of comment lines to total lines in the whole file
* Line locations where the line spills over 80 characters


We will elaborate on the scoring later in the report, because some of these metrics are purely for the sake of presenting actionable information. For example, “Number of whitespace lines in file”, independently, does not have any effect on the file’s score. It is displayed, though, for the sake of verbosity in the verbose report. It does, however, affect the ratio of comment lines to total lines in the whole file.

### Comment Metrics
In C++, there are several ways a programmer can make a comment. The comment style that came as the biggest surprise to us, is that with a “//” style comment, the programmer can extend the comment to the next line by inserting a “\” backslash to the end of the same line. This method of backslashing effectively creates a multi-line comment.

```
// This is an example of a C++ style multi-line \
comment. The '\' on the previous line creates a multi-line comment. \
backslashes can be chained together to extend the length of the multi-line comment. \
This last line is still commented out.
std::cout << "But this line is not commented out." << std::endl;
```

Our static code analyzer tracks every way a programmer can create a comment in C and C++, and creates distinctions based on style (inline, multi-line, full line). Note that “C style” refers to a comment made with “/*   */” and a “C++ style” comment refers to a comment made with “//”.

* “C style” inline comment
* “C++ style” inline comment
* “C style” full line comment
* “C++ style” full line comment
* “C style” multi-line comment
* “C++ style” multi-line comment

See the example below for a code visualization for each of the categories above:

```
int x = 0; /* This is a C style inline comment */
int y = 5; // This is a C++ style inline comment

/* This is a C style full line comment */
// This is a C++ style full line comment

// This is a C++ style multilined comment. Note how \
backslashing the previous line comments this line out.
/* This is a C style multilined comment.
It can span multiple lines.
*/
```



Though, in terms of syntax, there are only two primary methods of creating comments (/* */ vs. //), we decided to break each style into inline, full line, and multi-line comments for maximum detail and verbosity. Though our program only penalizes the user for inline comments, we believe it is helpful to provide line locations for each of the six styles. For example, if a company’s style guide declares that there should not be ANY multi-line comments using “C++ style” (// with the backslash at the end), a programmer at that company could use our static code analyzer to pinpoint the exact range of lines at which multi-line C++ style comments exist.

Excerpt of Verbose Report:
```
...
4 line location(s) with multi-line "/* */" style comments: 
  12-14
  18-24
  194-208
  603-655
...
```
By reading our verbose report, it is clear where the programmer would then look for multi-line comments within the file.

### Class Metrics
Currently, our Class Metrics category only checks for one metric: 
* Locations where class name is defined without a leading capital letter


We believe that not capitalizing class names is bad style, because when using the object in code, it could be visually misconstrued for a variable name.


Having a Class Metrics category promotes scalability for future versions of our code analyzer. In the future, we can implement further metrics that fall under the Class Metrics category such as:


* Class name quality (higher quality class names contain nouns)
* Average class name length
* Existence of explicitly defined “rule of three” methods if class private member data contains dynamically allocated memory


### Variable Metrics
Our Variable Metrics category analyzes source files for:

* Average variable length of primitive data types
* Median variable length of primitive data types


By primitive data types, we specifically mean:
```
bool
int
float
char
double
```
and the pointer type-variations of each: 
```
bool*
int**
float*****
char*
double**
```
Each primitive data type can handle as many pointer *’s that the programmer uses.

We included functionality for both average and median variable length, because statistically, median values exclude large outliers. An average variable length could be skewed if the programmer has one variable name that is 300 characters long. Contrasting the average variable length with the median variable length allows the user to quickly see if there are extreme outliers. In the future, we plan to expand the variable metrics analysis to analyze all data types instead of just primitive data types. Therefore, the program would then be able to test the variable name length of custom data types and custom objects. 


### Halstead Metrics
Our Halstead Metrics category is based on Maurice Halstead’s software measures he proposed in 1977. The basic premise behind Halstead’s complexity metrics is very simple: count the total and distinct number of Operators and Operands in a program. An Operator is a fixed symbol or reserved word in a programming language. Examples of such are: =, +, *, (), etc. An Operand is a quantity in which an operator is applied. Examples include identifiers and typenames such as long, double, int, float, bool, etc. Our static code analyzer tracks these four metrics for each source code file. In doing so, we are able to approximate the overall “maintainability” for each source file. A brief overview of Halstead’s calculations is as follows:

For any given program, let:

![Imgur](http://i.imgur.com/9qh3k30.png)


From  these numbers, several measures can be calculated:


![Imgur](http://i.imgur.com/Wcr55lN.png)

## Program Architecture

We have architected our class structure in a manner that promotes long term scalability and allows for easy additions of new metric categories. If we are raised with the hypothetical situation in which, last minute, we must add a metric as quickly as possible, we would be able to add it rather painlessly. If the new metric does not fall under a preexisting category, it wouldn’t be difficult to add a new parent category to house the new metric. See this basic, high-level diagram for an overview of our class architecture.



![Imgur](http://i.imgur.com/1qJ6ZuI.png)



Upon hitting the “Start” button, our program will create a “CodeAnalyzer” object, given a fully qualified path for the code base directory to scan. Using the fully qualified path to the directory, the FileFind object will recursively traverse through the directory (and all subfolders), to return to CodeAnalyzer, a vector of all file pathnames for files ending in “.c, .cpp, .h, and .hpp”. Then, by using the vector of each file’s pathname, CodeAnalyzer will create a “FileMetrics” object for each file. The FileMetrics object is a class that contains a CommentMetrics, LineMetrics, ClassMetrics, VariableMetrics, and HalsteadMetrics object. Each of these metric categories will calculate all its smaller, respective component metrics (such as LineMetrics’ number of lines in file, or VariableMetrics’ average variable length). There will be one FileMetrics object associated with each file in the traversed directory. Therefore, each file will contain its own unique comment metrics, line metrics, class metrics, etc. We have represented “...otherMetrics” in the high level diagram above in order to demonstrate the process of adding new metrics category. In the future, if we wish to add, for example,  a “FunctionMetrics” class, it would follow the same  pattern as all the other metric categories. Then, each file’s FileMetrics object would now contain a record of “FunctionMetrics”.


## C++ Parsing Methods

In the beginning stages of our project, our aim was to get started on coding as soon as possible. Thus, we tackled what we perceived to be the “easier” metrics first, such as “number of lines in the file”. In the spirit of getting code on paper as soon as possible, we stuck to strategies we already knew, like parsing text files, instead of learning how to use a new library such as the Elsa C/C++ parser. In order to find patterns such as “//” or “class Animal”, we treated the source file just like a text file and read the file character by character, searching for different patterns. Our method for parsing a file character by character is as follows:



```C++
ifstream fin(this->filename.c_str());
int numLines = 0;
char buffer;
while (fin.get(buffer))
{
    // Create a temporary char vector that holds a line of text
    Vector<char> currLine;
    
    // Increment the line counter
    numLines++

    // Reads until the buffer hits a newline character
    while (buffer != '\n')
    {
        // Add the current buffer
        currLine.add(buffer);
        // Get a new buffer
        fin.get(buffer);
    }
    // Adds the newline character to the end of the vector
    currLine.add(buffer);

    // Iterate through the current line to find patterns
    for (int i = 0; i < currLine.size(); i++)
    {
        // Search for patterns within the line
        // such as an occurrence of “/*” "?
    }
} 
```

Our C/C++ parsing methodology is a hybrid between reading line-by-line, and character-by- character, using two while loops. The outer layer while loop reads the first character of the line. Once we are inside the first while loop, a temporary vector of chars is created for the purpose of storing the contents of the rest of the line. Then, the inner while loop will read characters until it encounters the “newline” character. The for loop that follows allows us to traverse the current line, character by character, searching for a target pattern. For example, looking for a “//” C++ style full line comment:

```C++
// Flags that reset each new line
bool contentFound = false;

// Scans the entire line for analytics
for (int i = 0; i < currLine.size(); i++)
{
    // Check for cpp style comments
    if (currLine[i] == '/' && !contentFound)
    {
        if ((i + 1) <= currLine.size()-2)
        {
            // Check for "//" FULL LINE comments
            if (currLine[i + 1] == '/' && currLine[currLine.size()-2] != '\\')
            {
                this->numFullLineCommentsCpp++;
                this->locFullLineCpp.add(numLines);
            }
        }
    }
    
    // Check for first sighting of content
    if (currLine[i] > 32)
    {
        contentFound = true;
    }
}
```
The benefit of our C/C++ parsing method, is that we are able to both know the line number of the current line in the file, while also being able to easily traverse the line character by character.


Once we made ample progress on our project, we decided to branch out and diversify our metric categories. In order to gather information for Halstead Metrics’ operators and operands, it would have been extremely painful to utilize the character-by-character parsing method we used for LineMetrics and CommentMetrics. Searching for types that can vary, such as “char buffer, char \*buffer, char\* buffer”, we sought a more powerful tool that would save us time in parsing.

#### Regex

Regex is a powerful library that allows a user to search for patterns in text. We stopped using our own C/C++ parsing method once our methods became too verbose. For instance, in searching for operators for our HalsteadMetrics class, we could specify a search pattern: 

```C++
searchPattern = "(bool[* ]*)([a-zA-Z0-9_]+)|"
                "(int[* ]*)([a-zA-Z0-9_]+)|"
                "(float[* ]*)([a-zA-Z0-9_]+)|"
                "(char[* ]*)([a-zA-Z0-9_]+)|"
                "(double[* ]*)([a-zA-Z0-9_]+)|";
```

The search pattern searches for bool, int, float, char, or double types, and its accompanying identifier. From this one regex search pattern, we are now able to count instances of primitive data types, primitive data types pointer version, and the name of the variable. The regex search functionality is extremely powerful and saves a tremendous amount of time in searching for distinct terms. In the future, we will re-outfit the classes that used our own custom parsing algorithm with regex search patterns. Regex is not only more powerful of a tool, but also reduces the amount of code. Reducing the amount of code is not necessarily better, but the regex searching methodology is far easier to read than our nested loops.

## Scoring System
Our scoring system moves from 0 (being perfect) and grows without an upper bound. Any addition of points are deemed “negative” i.e. the programmer should aim for a low numerical score.

We score each codebase by first scoring each and every file within the codebase, and then averaging the scores of the individual files. Each individual file is normalized by length (source lines of code, or SLOC) so that each file’s scores can be compared with one another without regard to length. Therefore, it is easier to compare a huge file’s score to a smaller file’s score. When we calculate the final score for the program, it is the average score of each normalized file.

Our scoring metric is composed of 5 subscores, each weighted evenly. We have the ability to weight each individual submetric, should we desire to do so at a future date.

The first of our subscores is “Comment Metrics”. Our stance is that inline comments are poor practice. We came to this conclusion from the C++ style guide given at the beginning of this semester by our TAs. Should a different comment style become superior or desirable, we can easily modify our current source code to alter the scoring accordingly. We chose to add points to the score of the individual file by determining the percentage of inline comments--counting the number of inline comments and dividing by the SLOC in the file. The number of points we add to the total file’s score is based on the this percentage.

The second of our subscores is “Line Metrics”. Our stance is that comment density is an important statistic in analyzing whether or not source code is good code. After performing a fair amount of outside research, industry conventions seem to place acceptable comment density at approximately 20% of the source file. Therefore, we calculate the ratio of comment lines to the SLOC in the file. If the file meets or exceeds the 20% requirement, 0 points are added. If the file is determined to have less than 20%, but at least 15%, a small penalty is added to the score of the file. If the file is determined to have less than 15% of comment density, a large penalty is added to the source file’s score for the egregious offense of low comment density.

The third of our subscores is “Class Metrics”. Our stance is that not naming classes with a leading capital letter is a poor stylistic decision. We also believe that this stylistic decision should be punitive because this naming behavior rather easy to fix. Accordingly, we penalize by the number of improperly named classes in each source file. 

The fourth of our subscores is “Variable Metrics”. We track the average variable name length within the source file and penalize if the average is deemed too low. As of now, we consider an acceptable variable length average to be greater than 8. The threshold is easily modifiable in the future should we determine a better value for variable name length.

The fifth of our subscores is “Halstead Metrics”. Accordingly, we first calculate the distinct and total number of Operands and Operators within each source file. We then perform the calculations to obtain all of Halstead’s submetrics. These include: program length, vocabulary, difficulty in reading, the amount of effort it will take to code, etc. We then determine a maintainability index from these aforementioned values. As the file increases in length, there is a strong correlation it’s values as far as complexity and anticipated bugs will increase as well. Thus, the Halstead metric grows as the Total Lines of Code (TLOC )increases. Inherently, a code base requires effort to maintain, update, and debug. We feel that the this justifies our desire to increase the score due to growth of the file and, accordingly, the codebase.

The most important aspect of our current scoring system is the fact that we have the ability to tweak and modify how each of the five categories influences the final score. In the future, as we gather more data by running our code analyzer on different code bases, we will be able to tell if a particular category is contributing too much to the overall score. We can then either reduce or intensify a category’s impact on the final score.

## Annotated Output
![Imgur](http://i.imgur.com/2yIlC8F.png)
![Imgur](http://i.imgur.com/YhQ1J9e.png)


## Analysis of Various Code Bases
The three images below are overall scores for three different codebases. The full verbose outputs (in text file format) can be found in the "Verbose Reports of Various Enterprise Codebases" folder located in the base folder of this project. We ran analysis on Swift, FileZilla, 7zip, MongoDB, TensorFlow and more. See the leaderboard for all the codebases we tested.

Here is a leaderboard for different codebases we tested:


| Codebase     | Overall Score|
|:------------- |:-------------:|
|[TensorFlow](https://github.com/tensorflow/tensorflow)|27|
|[Facebook Proxygen](https://github.com/facebook/proxygen)|27|
|[NW.js](https://github.com/nwjs/nw.js)|28|
|[Electron](https://github.com/electron/electron)|29|
|Git -Good|31|
|[Facebook Folly](https://github.com/facebook/folly)|32|
|Luke, Oscar, Kellen's Search Engine|38|
|[Swift](https://github.com/apple/swift)|39|
|7zip|43|
|FileZilla|45|
|[MongoDB](https://github.com/mongodb/mongo)|45|
|KQ's Flight Planner|49|




The hyperlinked codebases link to the codebase's GitHub page. 




#### Apple's Swift
![Imgur](http://i.imgur.com/g3d7Gbt.png)
#### Git -Good (meta-recursion?? :hushed:)
![Imgur](http://i.imgur.com/KplHfZL.png)
#### Data Structures Sprint 2
![Imgur](http://i.imgur.com/UkNhXtR.png)
