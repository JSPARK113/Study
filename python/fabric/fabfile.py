from fabric import Config
from invoke import task

@task
def helloworld(ctx):
    print('hello world!')

@task
def f2(ctx, name='jae'):
    print('hello', name)