# Contributing

## Architecture

### UML

UML diagrams MUST be write using [planttext](https://www.planttext.com/).
The documentation about the language can be found [here](http://plantuml.com/guide).
If you use a [Jetbrains](https://www.jetbrains.com/) ide there is a [plugin](https://plugins.jetbrains.com/plugin/7017-plantuml-integration) that integrate PlantUML scripting language.
The file used to generate the uml can be found [here](./rtype.puml).

### Unit tests

Unit tests will be written using [criterion](https://github.com/Snaipe/Criterion).
The code coverage will be generated using [gcovr](https://gcovr.com/).
```shell script
# to generate line coverage
gcovr -r . --exclude client/tests/ --exclude server/tests/ --exclude commons/tests/
# to generate branches coverage
gcovr -r . --exclude client/tests/ --exclude server/tests/ --exclude commons/tests/ --branches
```

## Merge request

To be accepted a merge request must pass the following conditions:

### Changes

Every member of the groups must read all merge request and signal that they are ok with the changes

### Discussions

All discussions must be closed

### Code coverage

Every merge request (except GUI / Network or a good reason) must have at least 60% of code coverage.
The more branch coverage the better, try to not go under 60%.

### Documentation

Every merge request must have fully documented javadoc and the [uml file](./rtype.puml) up to date.