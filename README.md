# google-kickstart

![](https://img.shields.io/badge/Python-3.5-blue.svg)
![](https://img.shields.io/badge/numpy-1.16.2-green.svg)
![](https://img.shields.io/badge/scipy-1.2.1-green.svg)

Practice playground for google kickstart problems.

## Tips

- Think first.
- Solve on the visible tests first.
  - Be aware of the constraints for the visible tests, carefully.
  - Analyze the complexity.
  - Trivial ideas with moderate optimization could probably pass the tests.
- Then optimize the complexity for hidden tests.
- Avoid IDE and debugging tools if possible (for interview, where you can only code in google docs).

## Technical Tips

- Get familiar with the input/output format, prepare a template to handle I/O fast.
- Be aware of [the VERSION of the language and packages](https://codingcompetitions.withgoogle.com/kickstart/faq). If you want to test your code locally, build a virtual environment.
  > e.g. `fstring` is a new feature of python 3.6, which is NOT supported on the kickstart platform (python 3.5). [Ref](https://www.python.org/dev/peps/pep-0498/)
