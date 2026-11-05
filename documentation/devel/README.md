# Information specific for developers

You want to contribute to SimSET? Great!

- Read our Git [guidelines and recommendations](git-recommendations.md)
- Use `pre-commit` (required for serious development)

## Using pre-commit

We use [pre-commit](https://pre-commit.com) to check coding conventions, including white-space formatting rules.

### Installation

Just
```
pip/conda install pre-commit
```
However, we highly recommend to install `pre-commit` in your current `conda` enviroment or `venv`, so activate it first.

### "Manual" usage

```sh
git add blabla
pre-commit run
# optionally check files
# re"add" changes made by the hooks
git add blabla
git commit
```

## Enable pre-commit hooks
This will automatically run the pre-commit hooks at every commit.
```sh
cd /whereever/simset
pre-commit install
```

