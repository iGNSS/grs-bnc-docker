# Using Ubuntu 18.04 LTS
FROM ubuntu:20.04 as builder

# Install the software-properties-common Package (for add-apt-repository)
RUN apt-get update && apt-get install -y software-properties-common

# Add repository that has Qt4
RUN add-apt-repository ppa:rock-core/qt4

# Installing required packages
RUN apt-get update && apt-get install -y \
        build-essential \
        bash \
		supervisor \
		qt4-default \
		libqtwebkit4 \
        openssh-server \
        xauth \
    && sed -i "s/^.*X11Forwarding.*$/X11Forwarding yes/" /etc/ssh/sshd_config \
    && sed -i "s/^.*X11UseLocalhost.*$/X11UseLocalhost no/" /etc/ssh/sshd_config \
    && grep "^X11UseLocalhost" /etc/ssh/sshd_config || echo "X11UseLocalhost no" >> /etc/ssh/sshd_config
	
# Start ssh
RUN mkdir /var/run/sshd
RUN echo 'root:screencast' | chpasswd
RUN sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config

# SSH login fix. Otherwise user is kicked off after login
RUN sed 's@session\s*required\s*pam_loginuid.so@session optional pam_loginuid.so@g' -i /etc/pam.d/sshd

ENV NOTVISIBLE "in users profile"
RUN echo "export VISIBLE=now" >> /etc/profile
	
# Create folder for source codes
RUN mkdir -p /root/prog/

# Copy and compile BKG Standard NTRIP Caster
COPY bnc_source/BNC /root/prog/bnc/

# /root/prog/bnc/BNC_2.12.17

RUN qmake /root/./prog/bnc/bnc.pro
RUN make -C /root/prog/bnc/
RUN chmod +x /root/prog/bnc/bnc
RUN ln -s /root/prog/bnc/bnc /usr/bin/bnc

# Copy BNC configuration files
#ADD config /root/conf/

# Create folder for Supervisor log files
RUN mkdir -p /var/log/supervisor/

# Copy configuration files for Supervisor
COPY supervisord.conf /etc/supervisor/conf.d/supervisord.conf

EXPOSE 9001 22

CMD ["/usr/bin/supervisord"]		

