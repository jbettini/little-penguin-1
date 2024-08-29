# Little Penguin - Linux Kernel Development

This repository contains my solutions for the "Little Penguin - Linux Kernel Development" project. All tasks were completed on my own Linux From Scratch (LFS) distribution.

## About the Project

The "Little Penguin" project is a series of practical assignments designed to explore Linux kernel development. It covers various topics, such as compiling a custom kernel, writing kernel modules, managing devices, and more.

## Development Environment

I completed this project on my Linux From Scratch (LFS) distribution, which allowed me to learn how each component of the system interacts directly with the kernel. This approach provided greater control and a deeper understanding of the project's tasks.

## Prerequisites

To follow along with this project, you will need:

-    An LFS installation or another Linux distribution
-    Kernel development tools such as gcc, make, and git
-    Access to the Linux kernel sources (obtained from git.kernel.org)

## Instructions

-   Clone the Repository:
```
git clone https://github.com/jbettini/Little-Penguin-1.git
cd Little-Penguin-1
```
## Assignment

### Assignment 01: Custom Kernel Compilation

In this assignment, we compiled a custom Linux kernel from the source. Here are the steps I followed to complete this assignment:

-   First, I downloaded the latest version of the Linux kernel using Git:
```
    git clone --depth 1 https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git
    cd linux
```
-   Next, I configured the Linux kernel and enabled the CONFIG_LOCALVERSION_AUTO option to ensure the kernel version string includes a unique identifier:
```
    make mrproper
    make menuconfig
```
-   I followed the Linux From Scratch (LFS) guide to create the .config file needed for kernel compilation. You can find the detailed instructions here:
```
    [Linux From Scratch Kernel Configuration Guide](https://fr.linuxfromscratch.org/view/lfs-systemd-stable/chapter10/kernel.html)
```
-   I manually edited the .config file to ensure CONFIG_LOCALVERSION_AUTO is equal to y :
```
    CONFIG_LOCALVERSION_AUTO=y
```
-   After configuring, I compiled the kernel and installed the necessary modules:
```
make
make modules_install
cp -iv arch/x86/boot/bzImage /boot/vmlinuz-{Current Version of your repository}
cp -iv System.map /boot/System.map-{Current Version of your repository}
cp -iv .config /boot/config-{Current Version of your repository}
```
-   Finally, I updated the GRUB configuration to include the new kernel. Here’s an example entry added to /boot/grub/grub.cfg:
```
    menuentry 'Little-Penguin-1 ass0' {
        linux (hd0,msdos1)/vmlinuz-6.11-rc5 root=/dev/sda2 ro quiet
    }
```
Make sure to adjust the GRUB entry to match your specific setup and kernel version.
-   Reboot and Verify:
I rebooted the system to verify that the new kernel was loaded successfully.