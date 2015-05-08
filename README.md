# SEP_SS15
Softwareentwicklung Praktikum

Repository for SEP SS15 Basisbeispiel

**Authorized:**
* Lorenz Leitner
* Verena Niederwanger
* Markus Pichler

# TODO
- [x] ~~Rename exception files~~
- [x] ~~Fix return type in exception files~~
- [x] ~~Add exception class for write~~
- [x] ~~Implement board through AddTile (std::array)~~
- [x] ~~Make structs into classes~~
- [x] ~~Make write command (Provided map is sorted and with empty tiles)~~
- [x] ~~Make -g flag working~~
- [x] ~~Make AddTile check if valid move~~
- [x] ~~Forced tiles~~
- [x] ~~Add desctructor to every class (coding standard)~~
- [x] ~~Add exception class for other exceptions too (must be public)~~
- [x] ~~Implement try and catch in regular files using exception files~~
- [x] ~~Win condition columns and rows~~
- [x] ~~Win condition loop~~
- [x] ~~Fix issues~~
- [x] ~~Draw/Tie~~
- [ ] Figure out best way how to include exception classes in other files (baseexception class ?)
- [ ] Fix special test cases
- [ ] Do not include header files in header files (forward including ?)
- [ ] Check OutOfMemeroy exception on functionality

### Low priority
- [x] ~~Make commands into vector (see Fragestunde.md)~~
- [x] ~~Karte class translate to English~~
- [x] ~~Fix file headers mat. nr.~~
- [ ] Make write only append to file, not write a new one each time
- [ ] Add comments

### Vor Abgabe
- [x] ~~Make code coding standard conform~~
- [x] ~~Remove all output~~
- [x] ~~Compile with pluto and makefile~~
- [x] ~~Check valgrind~~
- [x] ~~Remove redundant/commented code~~

### Vor Ausbesserungsabgae
- [ ] Make code coding standard conform
- [ ] Remove all output
- [ ] Compile with pluto and makefile
- [ ] Check valgrind
- [ ] Remove redundant/commented code

### Feedback Gespräch
- [ ] exceptions
- [ ] memleak bei new fehler von tile
- [ ] 1 trax exception
- [ ] constructor mit "TRAX"
- [ ] write: class zu struct

- [x] vector<Command*> command_;
- [x] commands_.pushback(new Write());
- [x] Command *current_command = searchCommand[userinput[0]
- [x] current_command->.excecute(...)]

- [ ] using
- [ ] Karte
- [ ] deutsch

- [ ] ĥeader keine .h nur class

- [ ] initialisierungsliste! (AddTile, Game)

