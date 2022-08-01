FROM ros:melodic

RUN echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc
RUN apt update && apt install -y vim wget cmake
RUN rm /bin/sh && ln -s /bin/bash /bin/sh
RUN apt install -y ros-melodic-cv-bridge ros-melodic-tf ros-melodic-message-filters ros-melodic-image-transport ros-melodic-image-transport*
RUN apt install -y libcgal-dev pcl-tools

RUN git clone https://github.com/Livox-SDK/Livox-SDK.git
RUN cd Livox-SDK/build && cmake .. && make && make install

RUN mkdir -p ~/ws_livox/src
RUN git clone https://github.com/Livox-SDK/livox_ros_driver.git ~/ws_livox/src
RUN apt install -y ros-melodic-pcl-ros
RUN source /opt/ros/melodic/setup.bash && cd ~/ws_livox && catkin_make
RUN echo "source ~/ws_livox/devel/setup.bash" >> ~/.bashrc

RUN ln -s /usr/lib/python2.7/dist-packages/vtk/libvtkRenderingPythonTkWidgets.x86_64-linux-gnu.so /usr/lib/x86_64-linux-gnu/libvtkRenderingPythonTkWidgets.so
RUN ln -s /usr/bin/vtk6 /usr/bin/vtk
RUN apt install -y ros-melodic-eigen-conversions

RUN apt update
RUN apt install -y ros-melodic-cv-bridge
RUN sudo mv /usr/include/flann/ext/lz4.h /usr/include/flann/ext/lz4.h.bak && sudo mv /usr/include/flann/ext/lz4hc.h /usr/include/flann/ext/lz4.h.bak && sudo ln -s /usr/include/lz4.h /usr/include/flann/ext/lz4.h && sudo ln -s /usr/include/lz4hc.h /usr/include/flann/ext/lz4hc.h

RUN apt install -y ros-melodic-rviz
VOLUME ["~/rosbag"]
RUN touch ~/start.sh && chmod 755 ~/start.sh && echo "source ~/.bashrc"  >> ~/start.sh
RUN echo -e "source /opt/ros/melodic/setup.bash \n source ~/catkin_ws/devel/setup.bash" >> ~/start.sh
RUN echo "roslaunch mappingproxy mappingproxy.launch" >> ~/start.sh

RUN apt install at-spi2-core
RUN mkdir -p ~/catkin_ws/src
RUN cd ~/catkin_ws/src && git clone https://github.com/roboartisan-term/mappingproxy.git

RUN source /opt/ros/melodic/setup.bash &&  cd ~/catkin_ws/ && catkin_make
RUN echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc

CMD ["bash", "-c", "~/start.sh"]
