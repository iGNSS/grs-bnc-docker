# grs-bnc-docker
 Docker repository for BKG NTRIP Client (BNC)

* This is a repository for BNC. 
* The entrypoint for the container is sshd.
* BNC can be started from this container as a cli or a gui application. 

## Building the container
```docker build --rm -t gird:bnc .```

## Running the container
```docker run -d -p 9022:22 --name bnc gird:bnc```

## Accessing the container
```ssh -X -p 9022 root@localhost``` 
On windows you can for example use [MobaXterm](https://mobaxterm.mobatek.net/) to access ssh wit X-support
