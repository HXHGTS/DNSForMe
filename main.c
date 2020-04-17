#include<stdio.h>
#include<stdlib.h>

int mode;
FILE* yaml;
int main() {
	MainMenu:system("cls");
	printf("请选择DNS服务器运行方式：\n\n1.模式1：设置普通级别DNS解析（修改完成可以关闭本程序，部分域名会被污染）\n\n2.模式2：运行本地DNS（使用时不要关闭本窗口与弹出窗口，每次使用需要重新打开）\n\n3.恢复默认DNS（运行模式2时未正常退出，可用此选项恢复上网功能）\n\n4.DNS解析结果测试\n\n请输入：");
	scanf("%d", &mode);
	system("cls");
	if (mode == 2) {
		Config_gen();
		printf("正在部署DNS解析服务器. . .\n\n");
		system("start "" /min AdGuardHome.exe");
		printf("正在将DNS解析服务器设置为本地解析（可能会有报错，忽略即可）. . .\n\n");
		system("netsh interface ip set dns \"以太网\" static 127.0.0.1");
		system("netsh interface ipv6 set dns \"以太网\" static ::1");
		system("netsh interface ip set dns \"WLAN\" static 127.0.0.1");
		system("netsh interface ipv6 set dns \"WLAN\" static ::1");
		system("ipconfig /flushdns");
		system("cls");
		printf("正在进行DNS解析检测. . .\n\n");
		printf("正在检测国内网站. . .\n\n");
		printf("正在检测百度解析情况. . .\n\n");
		system("nslookup www.baidu.com 127.0.0.1");
		printf("正在检测腾讯解析情况. . .\n\n");
		system("nslookup www.qq.com 127.0.0.1");
		printf("正在检测英雄联盟解析情况. . .\n\n");
		system("nslookup lol.qq.com 127.0.0.1");
		printf("正在检测王者荣耀解析情况. . .\n\n");
		system("nslookup pvp.qq.com 127.0.0.1");
		printf("正在检测境外网站. . .\n\n");
		printf("正在检测谷歌解析情况. . .\n\n");
		system("nslookup www.google.com 127.0.0.1");
		printf("正在检测油管解析情况. . .\n\n");
		system("nslookup www.youtube.com 127.0.0.1");
		printf("正在检测脸书解析情况. . .\n\n");
		system("nslookup www.facebook.com 127.0.0.1");
		printf("正在检测推特解析情况. . .\n\n");
		system("nslookup twitter.com 127.0.0.1");
		printf("正在检测Twitch解析情况. . .\n\n");
		system("nslookup www.twitch.tv 127.0.0.1");
		printf("已完成对DNS解析的检测！\n\n");
		printf("DNS部署成功！\n\n");
		printf("-------------------------------------------------------------------------------------\n");
		printf("使用防污染DNS期间请不要关闭本窗口及其弹出窗口，后台最小化即可. . .\n");
		printf("注意：如需停止DNS解析请务必在本窗口中按任意键恢复默认DNS设置，否则会导致无法上网！！！\n");
		printf("如果不小心关闭本软件，可以重新打开本软件使用模式3恢复默认DNS！！！\n");
		printf("-------------------------------------------------------------------------------------\n");
		printf("如需恢复默认DNS设置，");
		system("pause");
		system("taskkill /f /im AdGuardHome.exe");
		system("netsh interface ip set dns \"以太网\" dhcp");
		system("netsh interface ipv6 set dns \"以太网\" dhcp");
		system("netsh interface ip set dns \"WLAN\" dhcp");
		system("netsh interface ipv6 set dns \"WLAN\" dhcp");
		system("ipconfig /flushdns");
		printf("\nDNS解析服务器已成功恢复初始设置！\n\n");
		system("pause");
		goto MainMenu;
	}
	else if (mode == 3) {
		system("taskkill /f /im AdGuardHome.exe");
		system("netsh interface ip set dns \"以太网\" dhcp");
		system("netsh interface ipv6 set dns \"以太网\" dhcp");
		system("netsh interface ip set dns \"WLAN\" dhcp");
		system("netsh interface ipv6 set dns \"WLAN\" dhcp");
		printf("DNS解析服务器已成功恢复初始设置！\n\n");
		system("ipconfig /flushdns");
		system("pause");
		goto MainMenu;
	}
	else if (mode == 1) {
		printf("可能会出现较长时间黑屏，请耐心等待. . .\n");
		system("netsh interface ip set dns \"以太网\" static 168.126.63.1");
		system("netsh interface ip add dns \"以太网\" 168.126.63.2 index=2");
		system("netsh interface ip set dns \"WLAN\" static 168.126.63.1");
		system("netsh interface ip add dns \"WLAN\" 168.126.63.2 index=2");
		printf("DNS解析服务器已成功设置为韩国KT DNS！\n\n");
		printf("此模式下，谷歌、油管、脸书、推特、Twitch等敏感域名仍会被污染！\n\n");
		printf("需要完全解析敏感域名请使用模式2！\n\n");
		system("ipconfig /flushdns");
		system("pause");
		goto MainMenu;
	}
	else if (mode == 4) {
		system("ipconfig /flushdns");
		printf("\n正在进行DNS解析检测. . .\n\n");
		printf("正在检测国内网站. . .\n\n");
		printf("正在检测百度解析情况. . .\n\n");
		system("nslookup www.baidu.com");
		printf("正在检测腾讯解析情况. . .\n\n");
		system("nslookup www.qq.com");
		printf("正在检测英雄联盟解析情况. . .\n\n");
		system("nslookup lol.qq.com");
		printf("正在检测王者荣耀解析情况. . .\n\n");
		system("nslookup pvp.qq.com");
		printf("正在检测境外网站. . .\n\n");
		printf("正在检测谷歌解析情况. . .\n\n");
		system("nslookup www.google.com");
		printf("正在检测油管解析情况. . .\n\n");
		system("nslookup www.youtube.com");
		printf("正在检测脸书解析情况. . .\n\n");
		system("nslookup www.facebook.com");
		printf("正在检测推特解析情况. . .\n\n");
		system("nslookup twitter.com");
		printf("正在检测Twitch解析情况. . .\n\n");
		system("nslookup www.twitch.tv");
		printf("可将解析出的ip地址放入在线ping工具中检测DNS污染情况！\n\n");
		printf("已完成对DNS解析的检测，");
		system("pause");
		goto MainMenu;
	}
	else {
		goto MainMenu;
	}
	return 0;
}

int Config_gen() {
		yaml = fopen("AdGuardHome.yaml", "w");
		fprintf(yaml, "bind_host: 0.0.0.0\nbind_port: 80\nusers:\n- name: root\n  password: $2a$10$mdmUKhmmhuDQO8GHlU.8xOWzwG6Fy.5o5YUCUWYg2DkyfgYRsM0hy\nhttp_proxy: ""\nlanguage: ""\nrlimit_nofile: 0\nweb_session_ttl: 720\ndns:\n  bind_host: 0.0.0.0\n  port: 53\n  statistics_interval: 1\n  querylog_enabled: false\n  querylog_interval: 90\n  querylog_size_memory: 1000\n  anonymize_client_ip: false\n  protection_enabled: true\n  blocking_mode: default\n  blocking_ipv4: \"\"\n  blocking_ipv6: \"\"\n  blocked_response_ttl: 10\n  ratelimit: 0\n  ratelimit_whitelist: []\n  refuse_any: true\n  bootstrap_dns:\n  - 114.114.114.114\n  all_servers: true\n  edns_client_subnet: true\n  enable_dnssec: false\n  aaaa_disabled: false\n  allowed_clients: []\n  disallowed_clients: []\n  blocked_hosts: []\n  parental_block_host: family-block.dns.adguard.com\n  safebrowsing_block_host: standard-block.dns.adguard.com\n  cache_size: 4194304\n  cache_ttl_min: 0\n  cache_ttl_max: 0\n  upstream_dns:\n  - 101.133.211.12:55\n  - tls://dns.sh.zhangmuhan.club\n  - https://dns.sh.zhangmuhan.club:444/dns-query\n  - '[/netease.com/]114.114.114.114'\n  - '[/126.net/]114.114.114.114'\n  - '[/icourse163.org/]114.114.114.114'\n  - '[/yeah.net/]114.114.114.114'\n  - '[/126.com/]114.114.114.114'\n  - '[/163.com/]114.114.114.114'\n  - '[/zhangmuhan.club/]114.114.114.114'\n  - '[/google.cn/]114.114.114.114'\n  - '[/baidu.com/]114.114.114.114'\n  - '[/baidupcs.com/]114.114.114.114'\n  - '[/bdstatic.com/]114.114.114.114'\n  - '[/bilibili.com/]114.114.114.114'\n  - '[/bilivideo.com/]114.114.114.114'\n  - '[/hdslb.com/]114.114.114.114'\n  - '[/qq.com/]114.114.114.114'\n  - '[/douyu.com/]114.114.114.114'\n  - '[/huya.com/]114.114.114.114'\n  - '[/aliyun.com/]114.114.114.114'\n  - '[/alicdn.com/]114.114.114.114'\n  - '[/alipay.com/]114.114.114.114'\n  - '[/taobao.com/]114.114.114.114'\n  - '[/tmall.com/]114.114.114.114'\n  - '[/jd.com/]114.114.114.114'\n  - '[/zxxk.com/]114.114.114.114'\n  - '[/cnzz.com/]114.114.114.114'\n  - '[/chaoxing.com/]114.114.114.114'\n  - '[/snnu.edu.cn/]114.114.114.114'\n  - '[/ipip.net/]114.114.114.114'\n  - '[/7moor.com/]114.114.114.114'\n  - '[/t.cn/]114.114.114.114'\n  - '[/chinaz.com/]114.114.114.114'\n  - '[/uzer.me/]114.114.114.114'\n  - '[/lanzou.com/]114.114.114.114'\n  - '[/lanzous.com/]114.114.114.114'\n  - '[/baidupan.com/]114.114.114.114'\n  - '[/zhihu.com/]114.114.114.114'\n  - '[/zhihu.com/]114.114.114.114'\n  - '[/zhimg.com/]114.114.114.114'\n  - '[/cnki.net/]114.114.114.114'\n  - '[/iqiyi.com/]114.114.114.114'\n  - '[/qy.net/]114.114.114.114'\n  - '[/iqiyipic.com/]114.114.114.114'\n  - '[/acfun.cn/]114.114.114.114'\n  - '[/aixifan.com/]114.114.114.114'\n  - '[/yximgs.com/]114.114.114.114'\n  - '[/ksurl.cn/]114.114.114.114'\n  - '[/139.com/]114.114.114.114'\n  - '[/10086.cn/]114.114.114.114'\n  - '[/189.cn/]114.114.114.114'\n  - '[/knet.cn/]114.114.114.114'\n  - '[/10010.cn/]114.114.114.114'\n  - '[/10010.com/]114.114.114.114'\n  - '[/weibo.com/]114.114.114.114'\n  - '[/sina.com.cn/]114.114.114.114'\n  - '[/sohu.com/]114.114.114.114'\n  - '[/cctv.cn/]114.114.114.114'\n  - '[/nn.com/]114.114.114.114'\n  - '[/xunyou.com/]114.114.114.114'\n  - '[/leigod.com/]114.114.114.114'\n  - '[/steampowered.com/]114.114.114.114'\n  - '[/eccdnx.com/]114.114.114.114'\n  - '[/iplaysoft.com/]114.114.114.114'\n  - '[/jianshu.com/]114.114.114.114'\n  filtering_enabled: true\n  filters_update_interval: 24\n  parental_enabled: false\n  safesearch_enabled: false\n  safebrowsing_enabled: false\n  safebrowsing_cache_size: 1048576\n  safesearch_cache_size: 1048576\n  parental_cache_size: 1048576\n  cache_time: 30\n  rewrites: []\n  blocked_services: []\ntls:\n  enabled: false\n  server_name: \"\"\n  force_https: false\n  port_https: 443\n  port_dns_over_tls: 853\n  allow_unencrypted_doh: false\n  strict_sni_check: false\n  certificate_chain: \"\"\n  private_key: \"\"\n  certificate_path: \"\"\n  private_key_path: \"\"\nfilters: []\nwhitelist_filters: []\nuser_rules:\n- 192.108.239.108 video-weaver.lhr03.hls.ttvnw.net\n- \"\"\ndhcp:\n  enabled: false\n  interface_name: \"\"\n  gateway_ip: \"\"\n  subnet_mask: \"\"\n  range_start: \"\"\n  range_end: \"\"\n  lease_duration: 86400\n  icmp_timeout_msec: 1000\nclients: []\nlog_file: \"\"\nverbose: false\nschema_version: 6\n");
		fclose(yaml);
	return 0;
}