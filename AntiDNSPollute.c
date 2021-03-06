﻿#include<stdio.h>
#include<stdlib.h>
int Boot();
int UserInterface();
int RunLocalDNSServer();
int NetFixTool();
int ConfigEditor();
int ConfigToDefault();
int NSTool();
int Help();
int FixHosts();
int Config_gen();
int Reset();
int Update();

int mode,DNSSet,fixmode,DNSServer,ADSwitch,ret,share;
FILE* yaml,*AdGuardHome,*SystemHosts,*bak,*ADFilter,*dll, * cv, * sv;
char ADFilterRules[536],domain[50],NSCommand[72],Adapter[60], WhiteList[2638],Command[120],adguard_current_version[15], adguard_source_version[15],anti_current_version[4]="5.1", anti_source_version[4];
char TopDNS[35] = "  - 119.29.29.29\n  - 119.28.28.28\n";//定义上游DNS服务器为腾讯DNS，与最终结果无关
char Hosts[6]="- \"\"\n";
char ABP_Filter[529]="\n- enabled: true\n  url: https://easylist-downloads.adblockplus.org/abp-filters-anti-cv.txt\n  name: ABP filters\n  id: 1588581704\n- enabled: true\n  url: https://easylist-downloads.adblockplus.org/easyprivacy.txt\n  name: EasyPrivacy\n  id: 1588581706\n- enabled: true\n  url: https://easylist-downloads.adblockplus.org/fanboy-social.txt\n  name: Fanboy's Social Blocking List\n  id: 1588581707\n- enabled: true\n  url: https://easylist-downloads.adblockplus.org/easylistchina+easylist.txt\n  name: EasyList China+EasyList\n  id: 1588581708\n";//ABP数据库
char AdGuard_Filter[533]="\n- enabled: true\n  url: https://filters.adtidy.org/extension/chromium/filters/2.txt\n  name: AdGuard Base filter\n  id: 1589448814\n- enabled: true\n  url: https://filters.adtidy.org/extension/chromium/filters/3.txt\n  name: AdGuard Tracking Protection filter\n  id: 1589448815\n- enabled: true\n  url: https://filters.adtidy.org/extension/chromium/filters/4.txt\n  name: AdGuard Social Media filter\n  id: 1589448816\n- enabled: true\n  url: https://easylist-downloads.adblockplus.org/easylistchina.txt\n  name: EasyList China\n  id: 1589448817\n";//AdGuard数据库

int UserInterface() {
	printf("请选择DNS服务器运行方式：\n\n1.运行本地DNS\n\n2.自定义DNS解析Hosts(仅模式1开启时有效)\n\n3.重置DNS（运行本地DNS时未正常退出，可用此选项恢复上网功能）\n\n4.自定义DNS配置文件（用于添加自定义上游）\n\n5.重置DNS配置文件（用户名密码也将被重置）\n\n6.纯净解析结果获取（不修改本机DNS）\n\n7.重置系统Hosts文件\n\n8.检查AdGuardHome更新\n\n9.在线帮助\n\n0.退出\n\n请输入：");
	ret=scanf("%d", &mode);
	system("cls");
	return 0;
}

int main() {
	system("color 0B");
MainMenu:system("cls");
	UserInterface();
	if (mode == 1) {
		if (Boot() != 0) {
			printf("未在软件目录中发现AdGuardHome引擎，请在官网下载后放置在本软件同一目录下！\n\n");
			system("explorer https://github.com/AdguardTeam/AdGuardHome/releases/latest/download/AdGuardHome_windows_amd64.zip");
			system("pause");
			goto MainMenu;
		}
		system("cls");
		RunLocalDNSServer();
		goto MainMenu;
	}
	else if (mode == 2) {
		Boot();
		system("cls");
		printf("请在弹出窗口中修改，记得保存. . .\n");
		system("notepad hosts");
		goto MainMenu;
	}
	else if (mode == 3) {
		NetFixTool();
		goto MainMenu;
	}
	else if (mode == 4) {
		Boot();
		if (Boot() != 0) {
			printf("未在软件目录中发现AdGuardHome引擎，请在官网下载后放置在本软件同一目录下！\n\n");
			system("explorer https://github.com/AdguardTeam/AdGuardHome/releases/latest/download/AdGuardHome_windows_amd64.zip");
			system("pause");
			goto MainMenu;
		}
		system("cls");
		ConfigEditor();
		goto MainMenu;
}
	else if (mode == 5) {
		Boot();
		if (Boot() != 0) {
			printf("未在软件目录中发现AdGuardHome引擎，请在官网下载后放置在本软件同一目录下！\n\n");
			system("explorer https://github.com/AdguardTeam/AdGuardHome/releases/latest/download/AdGuardHome_windows_amd64.zip");
			system("pause");
			goto MainMenu;
		}
		system("cls");
		ConfigToDefault();
		goto MainMenu;
}
	else if (mode == 6) {
		NSTool();
		goto MainMenu;
	}
	else if (mode == 7) {
		FixHosts();
		goto MainMenu;
	}
	else if (mode == 8) {
		Update();
		goto MainMenu;
	}
	else if (mode == 9) {
		Help();
		goto MainMenu;
}
	else if (mode == 0) {
		exit(0);
	}
	else {
		goto MainMenu;
	}
	return 0;
}

int Config_gen() {
	char bind_ip[10];
		printf("指定上游DNS服务器区域：\n\n1.OpenDNS\n\n2.Google\n\n3.Quad9\n\n4.Cloudflare\n\n5.Quad101\n\n6.AdGuard\n\n7.NextDNS\n\n8.IIJ\n\n请输入：");
		ret=scanf("%d", &DNSServer);
		system("cls");
		printf("广告拦截模式：\n\n1.Adblock Plus\n\n2.AdGuard\n\n3.不拦截\n\n请输入：");
		ret=scanf("%d", &ADSwitch);
		printf("\n是否支持局域网共享DNS：\n\n1.是\n\n2.否\n\n请输入：");
		ret = scanf("%d", &share);
		system("cls");
		yaml = fopen("index.yaml", "w");
		if (ADSwitch == 1) {
			sprintf(ADFilterRules, "%s", ABP_Filter);

		}
		else if (ADSwitch == 2) {
			sprintf(ADFilterRules, "%s", AdGuard_Filter);
		}
		else {
			sprintf(ADFilterRules, "[]\n");
		}
		if (share == 1) {
			sprintf(bind_ip, "0.0.0.0");
		}
		else {
			sprintf(bind_ip, "127.0.0.1");
		}
		sprintf(WhiteList, "  - '[/cn/]tls://dns.pub'\n  - '[/steampowered.com/]tls://dns.pub'\n  - '[/steamgames.com/]tls://dns.pub'\n  - '[/steamusercontent.com/]tls://dns.pub'\n  - '[/steamcontent.com/]tls://dns.pub'\n  - '[/steamstatic.com/]tls://dns.pub'\n  - '[/pinyuncloud.com/]tls://dns.pub'\n  - '[/netease.com/]tls://dns.pub'\n  - '[/126.net/]tls://dns.pub'\n  - '[/icourse163.org/]tls://dns.pub'\n  - '[/yeah.net/]tls://dns.pub'\n  - '[/126.com/]tls://dns.pub'\n  - '[/163.com/]tls://dns.pub'\n  - '[/recaptcha.net/]tls://dns.pub'\n  - '[/gstatic.com/]tls://dns.pub'\n  - '[/googleapis.com/]tls://dns.pub'\n  - '[/google.cn/]tls://dns.pub'\n  - '[/baidu.com/]tls://dns.pub'\n  - '[/baidupcs.com/]tls://dns.pub'\n  - '[/bdstatic.com/]tls://dns.pub'\n  - '[/bilibili.com/]tls://dns.pub'\n  - '[/geetest.com/]tls://dns.pub'\n  - '[/bilivideo.com/]tls://dns.pub'\n  - '[/akamaized.net/]tls://dns.pub'\n  - '[/hdslb.com/]tls://dns.pub'\n  - '[/qq.com/]tls://dns.pub'\n  - '[/douyu.com/]tls://dns.pub'\n  - '[/huya.com/]tls://dns.pub'\n  - '[/aliyun.com/]tls://dns.pub'\n  - '[/aliyuncs.com/]tls://dns.pub'\n  - '[/alicdn.com/]tls://dns.pub'\n  - '[/alipay.com/]tls://dns.pub'\n  - '[/taobao.com/]tls://dns.pub'\n  - '[/tmall.com/]tls://dns.pub'\n  - '[/jd.com/]tls://dns.pub'\n  - '[/zxxk.com/]tls://dns.pub'\n  - '[/cnzz.com/]tls://dns.pub'\n  - '[/chaoxing.com/]tls://dns.pub'\n  - '[/ipip.net/]tls://dns.pub'\n  - '[/7moor.com/]tls://dns.pub'\n  - '[/t.cn/]tls://dns.pub'\n  - '[/chinaz.com/]tls://dns.pub'\n  - '[/uzer.me/]tls://dns.pub'\n  - '[/lanzou.com/]tls://dns.pub'\n  - '[/lanzous.com/]tls://dns.pub'\n  - '[/baidupan.com/]tls://dns.pub'\n  - '[/v.smtcdns.com/]tls://dns.pub'\n  - '[/youku.com/]tls://dns.pub'\n  - '[/ott.cibntv.net/]tls://dns.pub'\n  - '[/zhihu.com/]tls://dns.pub'\n  - '[/zhimg.com/]tls://dns.pub'\n  - '[/cnki.net/]tls://dns.pub'\n  - '[/iqiyi.com/]tls://dns.pub'\n  - '[/qy.net/]tls://dns.pub'\n  - '[/iqiyipic.com/]tls://dns.pub'\n  - '[/acfun.cn/]tls://dns.pub'\n  - '[/aixifan.com/]tls://dns.pub'\n  - '[/yximgs.com/]tls://dns.pub'\n  - '[/ksurl.cn/]tls://dns.pub'\n  - '[/139.com/]tls://dns.pub'\n  - '[/10086.cn/]tls://dns.pub'\n  - '[/189.cn/]tls://dns.pub'\n  - '[/knet.cn/]tls://dns.pub'\n  - '[/10010.cn/]tls://dns.pub'\n  - '[/10010.com/]tls://dns.pub'\n  - '[/weibo.com/]tls://dns.pub'\n  - '[/sina.com.cn/]tls://dns.pub'\n  - '[/sohu.com/]tls://dns.pub'\n  - '[/cctv.cn/]tls://dns.pub'\n  - '[/nn.com/]tls://dns.pub'\n  - '[/xunyou.com/]tls://dns.pub'\n  - '[/leigod.com/]tls://dns.pub'\n  - '[/gitee.io/]tls://dns.pub'\n  - '[/eccdnx.com/]tls://dns.pub'\n  - '[/iplaysoft.com/]tls://dns.pub'\n  - '[/jianshu.com/]tls://dns.pub'\n  - '[/edu.cn/]tls://dns.pub'\n  - '[/gov.cn/]tls://dns.pub'\n");//常用国内域名分流
		if (DNSServer == 1)fprintf(yaml, "bind_host: %s\nbind_port: 80\nusers:\n- name: root\n  password: $2a$10$mdmUKhmmhuDQO8GHlU.8xOWzwG6Fy.5o5YUCUWYg2DkyfgYRsM0hy\nhttp_proxy: ""\nlanguage: ""\nrlimit_nofile: 0\nweb_session_ttl: 720\ndns:\n  bind_host: %s\n  port: 53\n  statistics_interval: 1\n  querylog_enabled: true\n  querylog_interval: 90\n  querylog_size_memory: 1000\n  anonymize_client_ip: false\n  protection_enabled: true\n  blocking_mode: default\n  blocking_ipv4: \"\"\n  blocking_ipv6: \"\"\n  blocked_response_ttl: 10\n  ratelimit: 0\n  ratelimit_whitelist: []\n  refuse_any: true\n  bootstrap_dns:\n%s  all_servers: false\n  fastest_addr: false\n  edns_client_subnet: true\n  enable_dnssec: false\n  aaaa_disabled: false\n  allowed_clients: []\n  disallowed_clients: []\n  blocked_hosts: []\n  parental_block_host: family-block.dns.adguard.com\n  safebrowsing_block_host: standard-block.dns.adguard.com\n  cache_size: 0\n  cache_ttl_min: 0\n  cache_ttl_max: 0\n  upstream_dns:\n%s%s  filtering_enabled: true\n  filters_update_interval: 24\n  parental_enabled: false\n  safesearch_enabled: false\n  safebrowsing_enabled: false\n  safebrowsing_cache_size: 1048576\n  safesearch_cache_size: 1048576\n  parental_cache_size: 1048576\n  cache_time: 30\n  rewrites: []\n  blocked_services: []\ntls:\n  enabled: false\n  server_name: \"\"\n  force_https: false\n  port_https: 443\n  port_dns_over_tls: 853\n  allow_unencrypted_doh: false\n  strict_sni_check: false\n  certificate_chain: \"\"\n  private_key: \"\"\n  certificate_path: \"\"\n  private_key_path: \"\"\nfilters: %swhitelist_filters: []\nuser_rules:\n%sdhcp:\n  enabled: false\n  interface_name: \"\"\n  gateway_ip: \"\"\n  subnet_mask: \"\"\n  range_start: \"\"\n  range_end: \"\"\n  lease_duration: 86400\n  icmp_timeout_msec: 400\nclients: []\nlog_file: \"\"\nverbose: false\nschema_version: 6\n", bind_ip,bind_ip,TopDNS,  "  - https://doh.opendns.com/dns-query\n", WhiteList, ADFilterRules, Hosts);
		else if (DNSServer == 2)fprintf(yaml, "bind_host: %s\nbind_port: 80\nusers:\n- name: root\n  password: $2a$10$mdmUKhmmhuDQO8GHlU.8xOWzwG6Fy.5o5YUCUWYg2DkyfgYRsM0hy\nhttp_proxy: ""\nlanguage: ""\nrlimit_nofile: 0\nweb_session_ttl: 720\ndns:\n  bind_host: %s\n  port: 53\n  statistics_interval: 1\n  querylog_enabled: true\n  querylog_interval: 90\n  querylog_size_memory: 1000\n  anonymize_client_ip: false\n  protection_enabled: true\n  blocking_mode: default\n  blocking_ipv4: \"\"\n  blocking_ipv6: \"\"\n  blocked_response_ttl: 10\n  ratelimit: 0\n  ratelimit_whitelist: []\n  refuse_any: true\n  bootstrap_dns:\n%s  all_servers: false\n  fastest_addr: false\n  edns_client_subnet: true\n  enable_dnssec: false\n  aaaa_disabled: false\n  allowed_clients: []\n  disallowed_clients: []\n  blocked_hosts: []\n  parental_block_host: family-block.dns.adguard.com\n  safebrowsing_block_host: standard-block.dns.adguard.com\n  cache_size: 0\n  cache_ttl_min: 0\n  cache_ttl_max: 0\n  upstream_dns:\n%s%s  filtering_enabled: true\n  filters_update_interval: 24\n  parental_enabled: false\n  safesearch_enabled: false\n  safebrowsing_enabled: false\n  safebrowsing_cache_size: 1048576\n  safesearch_cache_size: 1048576\n  parental_cache_size: 1048576\n  cache_time: 30\n  rewrites: []\n  blocked_services: []\ntls:\n  enabled: false\n  server_name: \"\"\n  force_https: false\n  port_https: 443\n  port_dns_over_tls: 853\n  allow_unencrypted_doh: false\n  strict_sni_check: false\n  certificate_chain: \"\"\n  private_key: \"\"\n  certificate_path: \"\"\n  private_key_path: \"\"\nfilters: %swhitelist_filters: []\nuser_rules:\n%sdhcp:\n  enabled: false\n  interface_name: \"\"\n  gateway_ip: \"\"\n  subnet_mask: \"\"\n  range_start: \"\"\n  range_end: \"\"\n  lease_duration: 86400\n  icmp_timeout_msec: 400\nclients: []\nlog_file: \"\"\nverbose: false\nschema_version: 6\n", bind_ip,bind_ip,TopDNS,  "  - tls://dns.google:853\n", WhiteList, ADFilterRules, Hosts);
		else if (DNSServer == 3)fprintf(yaml, "bind_host: %s\nbind_port: 80\nusers:\n- name: root\n  password: $2a$10$mdmUKhmmhuDQO8GHlU.8xOWzwG6Fy.5o5YUCUWYg2DkyfgYRsM0hy\nhttp_proxy: ""\nlanguage: ""\nrlimit_nofile: 0\nweb_session_ttl: 720\ndns:\n  bind_host: %s\n  port: 53\n  statistics_interval: 1\n  querylog_enabled: true\n  querylog_interval: 90\n  querylog_size_memory: 1000\n  anonymize_client_ip: false\n  protection_enabled: true\n  blocking_mode: default\n  blocking_ipv4: \"\"\n  blocking_ipv6: \"\"\n  blocked_response_ttl: 10\n  ratelimit: 0\n  ratelimit_whitelist: []\n  refuse_any: true\n  bootstrap_dns:\n%s  all_servers: false\n  fastest_addr: false\n  edns_client_subnet: true\n  enable_dnssec: false\n  aaaa_disabled: false\n  allowed_clients: []\n  disallowed_clients: []\n  blocked_hosts: []\n  parental_block_host: family-block.dns.adguard.com\n  safebrowsing_block_host: standard-block.dns.adguard.com\n  cache_size: 0\n  cache_ttl_min: 0\n  cache_ttl_max: 0\n  upstream_dns:\n%s%s  filtering_enabled: true\n  filters_update_interval: 24\n  parental_enabled: false\n  safesearch_enabled: false\n  safebrowsing_enabled: false\n  safebrowsing_cache_size: 1048576\n  safesearch_cache_size: 1048576\n  parental_cache_size: 1048576\n  cache_time: 30\n  rewrites: []\n  blocked_services: []\ntls:\n  enabled: false\n  server_name: \"\"\n  force_https: false\n  port_https: 443\n  port_dns_over_tls: 853\n  allow_unencrypted_doh: false\n  strict_sni_check: false\n  certificate_chain: \"\"\n  private_key: \"\"\n  certificate_path: \"\"\n  private_key_path: \"\"\nfilters: %swhitelist_filters: []\nuser_rules:\n%sdhcp:\n  enabled: false\n  interface_name: \"\"\n  gateway_ip: \"\"\n  subnet_mask: \"\"\n  range_start: \"\"\n  range_end: \"\"\n  lease_duration: 86400\n  icmp_timeout_msec: 400\nclients: []\nlog_file: \"\"\nverbose: false\nschema_version: 6\n", bind_ip,bind_ip,TopDNS,  "  - https://dns.quad9.net/dns-query\n  - https://dns11.quad9.net/dns-query\n", WhiteList, ADFilterRules, Hosts);
		else if (DNSServer == 4)fprintf(yaml, "bind_host: %s\nbind_port: 80\nusers:\n- name: root\n  password: $2a$10$mdmUKhmmhuDQO8GHlU.8xOWzwG6Fy.5o5YUCUWYg2DkyfgYRsM0hy\nhttp_proxy: ""\nlanguage: ""\nrlimit_nofile: 0\nweb_session_ttl: 720\ndns:\n  bind_host: %s\n  port: 53\n  statistics_interval: 1\n  querylog_enabled: true\n  querylog_interval: 90\n  querylog_size_memory: 1000\n  anonymize_client_ip: false\n  protection_enabled: true\n  blocking_mode: default\n  blocking_ipv4: \"\"\n  blocking_ipv6: \"\"\n  blocked_response_ttl: 10\n  ratelimit: 0\n  ratelimit_whitelist: []\n  refuse_any: true\n  bootstrap_dns:\n%s  all_servers: false\n  fastest_addr: false\n  edns_client_subnet: true\n  enable_dnssec: false\n  aaaa_disabled: false\n  allowed_clients: []\n  disallowed_clients: []\n  blocked_hosts: []\n  parental_block_host: family-block.dns.adguard.com\n  safebrowsing_block_host: standard-block.dns.adguard.com\n  cache_size: 0\n  cache_ttl_min: 0\n  cache_ttl_max: 0\n  upstream_dns:\n%s%s  filtering_enabled: true\n  filters_update_interval: 24\n  parental_enabled: false\n  safesearch_enabled: false\n  safebrowsing_enabled: false\n  safebrowsing_cache_size: 1048576\n  safesearch_cache_size: 1048576\n  parental_cache_size: 1048576\n  cache_time: 30\n  rewrites: []\n  blocked_services: []\ntls:\n  enabled: false\n  server_name: \"\"\n  force_https: false\n  port_https: 443\n  port_dns_over_tls: 853\n  allow_unencrypted_doh: false\n  strict_sni_check: false\n  certificate_chain: \"\"\n  private_key: \"\"\n  certificate_path: \"\"\n  private_key_path: \"\"\nfilters: %swhitelist_filters: []\nuser_rules:\n%sdhcp:\n  enabled: false\n  interface_name: \"\"\n  gateway_ip: \"\"\n  subnet_mask: \"\"\n  range_start: \"\"\n  range_end: \"\"\n  lease_duration: 86400\n  icmp_timeout_msec: 400\nclients: []\nlog_file: \"\"\nverbose: false\nschema_version: 6\n", bind_ip,bind_ip,TopDNS,  "  - https://cloudflare-dns.com/dns-query\n", WhiteList, ADFilterRules, Hosts);
		else if (DNSServer == 5)fprintf(yaml, "bind_host: %s\nbind_port: 80\nusers:\n- name: root\n  password: $2a$10$mdmUKhmmhuDQO8GHlU.8xOWzwG6Fy.5o5YUCUWYg2DkyfgYRsM0hy\nhttp_proxy: ""\nlanguage: ""\nrlimit_nofile: 0\nweb_session_ttl: 720\ndns:\n  bind_host: %s\n  port: 53\n  statistics_interval: 1\n  querylog_enabled: true\n  querylog_interval: 90\n  querylog_size_memory: 1000\n  anonymize_client_ip: false\n  protection_enabled: true\n  blocking_mode: default\n  blocking_ipv4: \"\"\n  blocking_ipv6: \"\"\n  blocked_response_ttl: 10\n  ratelimit: 0\n  ratelimit_whitelist: []\n  refuse_any: true\n  bootstrap_dns:\n%s  all_servers: false\n  fastest_addr: false\n  edns_client_subnet: true\n  enable_dnssec: false\n  aaaa_disabled: false\n  allowed_clients: []\n  disallowed_clients: []\n  blocked_hosts: []\n  parental_block_host: family-block.dns.adguard.com\n  safebrowsing_block_host: standard-block.dns.adguard.com\n  cache_size: 0\n  cache_ttl_min: 0\n  cache_ttl_max: 0\n  upstream_dns:\n%s%s  filtering_enabled: true\n  filters_update_interval: 24\n  parental_enabled: false\n  safesearch_enabled: false\n  safebrowsing_enabled: false\n  safebrowsing_cache_size: 1048576\n  safesearch_cache_size: 1048576\n  parental_cache_size: 1048576\n  cache_time: 30\n  rewrites: []\n  blocked_services: []\ntls:\n  enabled: false\n  server_name: \"\"\n  force_https: false\n  port_https: 443\n  port_dns_over_tls: 853\n  allow_unencrypted_doh: false\n  strict_sni_check: false\n  certificate_chain: \"\"\n  private_key: \"\"\n  certificate_path: \"\"\n  private_key_path: \"\"\nfilters: %swhitelist_filters: []\nuser_rules:\n%sdhcp:\n  enabled: false\n  interface_name: \"\"\n  gateway_ip: \"\"\n  subnet_mask: \"\"\n  range_start: \"\"\n  range_end: \"\"\n  lease_duration: 86400\n  icmp_timeout_msec: 400\nclients: []\nlog_file: \"\"\nverbose: false\nschema_version: 6\n", bind_ip,bind_ip,TopDNS, "  - https://dns.twnic.tw/dns-query\n", WhiteList, ADFilterRules, Hosts);
		else if (DNSServer == 6)fprintf(yaml, "bind_host: %s\nbind_port: 80\nusers:\n- name: root\n  password: $2a$10$mdmUKhmmhuDQO8GHlU.8xOWzwG6Fy.5o5YUCUWYg2DkyfgYRsM0hy\nhttp_proxy: ""\nlanguage: ""\nrlimit_nofile: 0\nweb_session_ttl: 720\ndns:\n  bind_host: %s\n  port: 53\n  statistics_interval: 1\n  querylog_enabled: true\n  querylog_interval: 90\n  querylog_size_memory: 1000\n  anonymize_client_ip: false\n  protection_enabled: true\n  blocking_mode: default\n  blocking_ipv4: \"\"\n  blocking_ipv6: \"\"\n  blocked_response_ttl: 10\n  ratelimit: 0\n  ratelimit_whitelist: []\n  refuse_any: true\n  bootstrap_dns:\n%s  all_servers: false\n  fastest_addr: false\n  edns_client_subnet: true\n  enable_dnssec: false\n  aaaa_disabled: false\n  allowed_clients: []\n  disallowed_clients: []\n  blocked_hosts: []\n  parental_block_host: family-block.dns.adguard.com\n  safebrowsing_block_host: standard-block.dns.adguard.com\n  cache_size: 0\n  cache_ttl_min: 0\n  cache_ttl_max: 0\n  upstream_dns:\n%s%s  filtering_enabled: true\n  filters_update_interval: 24\n  parental_enabled: false\n  safesearch_enabled: false\n  safebrowsing_enabled: false\n  safebrowsing_cache_size: 1048576\n  safesearch_cache_size: 1048576\n  parental_cache_size: 1048576\n  cache_time: 30\n  rewrites: []\n  blocked_services: []\ntls:\n  enabled: false\n  server_name: \"\"\n  force_https: false\n  port_https: 443\n  port_dns_over_tls: 853\n  allow_unencrypted_doh: false\n  strict_sni_check: false\n  certificate_chain: \"\"\n  private_key: \"\"\n  certificate_path: \"\"\n  private_key_path: \"\"\nfilters: %swhitelist_filters: []\nuser_rules:\n%sdhcp:\n  enabled: false\n  interface_name: \"\"\n  gateway_ip: \"\"\n  subnet_mask: \"\"\n  range_start: \"\"\n  range_end: \"\"\n  lease_duration: 86400\n  icmp_timeout_msec: 400\nclients: []\nlog_file: \"\"\nverbose: false\nschema_version: 6\n", bind_ip,bind_ip, TopDNS, "  - https://dns.adguard.com/dns-query\n", WhiteList, ADFilterRules, Hosts);
		else if (DNSServer == 7)fprintf(yaml, "bind_host: %s\nbind_port: 80\nusers:\n- name: root\n  password: $2a$10$mdmUKhmmhuDQO8GHlU.8xOWzwG6Fy.5o5YUCUWYg2DkyfgYRsM0hy\nhttp_proxy: ""\nlanguage: ""\nrlimit_nofile: 0\nweb_session_ttl: 720\ndns:\n  bind_host: %s\n  port: 53\n  statistics_interval: 1\n  querylog_enabled: true\n  querylog_interval: 90\n  querylog_size_memory: 1000\n  anonymize_client_ip: false\n  protection_enabled: true\n  blocking_mode: default\n  blocking_ipv4: \"\"\n  blocking_ipv6: \"\"\n  blocked_response_ttl: 10\n  ratelimit: 0\n  ratelimit_whitelist: []\n  refuse_any: true\n  bootstrap_dns:\n%s  all_servers: false\n  fastest_addr: false\n  edns_client_subnet: true\n  enable_dnssec: false\n  aaaa_disabled: false\n  allowed_clients: []\n  disallowed_clients: []\n  blocked_hosts: []\n  parental_block_host: family-block.dns.adguard.com\n  safebrowsing_block_host: standard-block.dns.adguard.com\n  cache_size: 0\n  cache_ttl_min: 0\n  cache_ttl_max: 0\n  upstream_dns:\n%s%s  filtering_enabled: true\n  filters_update_interval: 24\n  parental_enabled: false\n  safesearch_enabled: false\n  safebrowsing_enabled: false\n  safebrowsing_cache_size: 1048576\n  safesearch_cache_size: 1048576\n  parental_cache_size: 1048576\n  cache_time: 30\n  rewrites: []\n  blocked_services: []\ntls:\n  enabled: false\n  server_name: \"\"\n  force_https: false\n  port_https: 443\n  port_dns_over_tls: 853\n  allow_unencrypted_doh: false\n  strict_sni_check: false\n  certificate_chain: \"\"\n  private_key: \"\"\n  certificate_path: \"\"\n  private_key_path: \"\"\nfilters: %swhitelist_filters: []\nuser_rules:\n%sdhcp:\n  enabled: false\n  interface_name: \"\"\n  gateway_ip: \"\"\n  subnet_mask: \"\"\n  range_start: \"\"\n  range_end: \"\"\n  lease_duration: 86400\n  icmp_timeout_msec: 400\nclients: []\nlog_file: \"\"\nverbose: false\nschema_version: 6\n", bind_ip,bind_ip, TopDNS, "  - https://dns.nextdns.io/dns-query\n", WhiteList, ADFilterRules, Hosts);
		else fprintf(yaml, "bind_host: %s\nbind_port: 80\nusers:\n- name: root\n  password: $2a$10$mdmUKhmmhuDQO8GHlU.8xOWzwG6Fy.5o5YUCUWYg2DkyfgYRsM0hy\nhttp_proxy: ""\nlanguage: ""\nrlimit_nofile: 0\nweb_session_ttl: 720\ndns:\n  bind_host: %s\n  port: 53\n  statistics_interval: 1\n  querylog_enabled: true\n  querylog_interval: 90\n  querylog_size_memory: 1000\n  anonymize_client_ip: false\n  protection_enabled: true\n  blocking_mode: default\n  blocking_ipv4: \"\"\n  blocking_ipv6: \"\"\n  blocked_response_ttl: 10\n  ratelimit: 0\n  ratelimit_whitelist: []\n  refuse_any: true\n  bootstrap_dns:\n%s  all_servers: false\n  fastest_addr: false\n  edns_client_subnet: true\n  enable_dnssec: false\n  aaaa_disabled: false\n  allowed_clients: []\n  disallowed_clients: []\n  blocked_hosts: []\n  parental_block_host: family-block.dns.adguard.com\n  safebrowsing_block_host: standard-block.dns.adguard.com\n  cache_size: 0\n  cache_ttl_min: 0\n  cache_ttl_max: 0\n  upstream_dns:\n%s%s  filtering_enabled: true\n  filters_update_interval: 24\n  parental_enabled: false\n  safesearch_enabled: false\n  safebrowsing_enabled: false\n  safebrowsing_cache_size: 1048576\n  safesearch_cache_size: 1048576\n  parental_cache_size: 1048576\n  cache_time: 30\n  rewrites: []\n  blocked_services: []\ntls:\n  enabled: false\n  server_name: \"\"\n  force_https: false\n  port_https: 443\n  port_dns_over_tls: 853\n  allow_unencrypted_doh: false\n  strict_sni_check: false\n  certificate_chain: \"\"\n  private_key: \"\"\n  certificate_path: \"\"\n  private_key_path: \"\"\nfilters: %swhitelist_filters: []\nuser_rules:\n%sdhcp:\n  enabled: false\n  interface_name: \"\"\n  gateway_ip: \"\"\n  subnet_mask: \"\"\n  range_start: \"\"\n  range_end: \"\"\n  lease_duration: 86400\n  icmp_timeout_msec: 400\nclients: []\nlog_file: \"\"\nverbose: false\nschema_version: 6\n", bind_ip, bind_ip, TopDNS, "  - https://public.dns.iij.jp/dns-query\n", WhiteList, ADFilterRules, Hosts);
		fclose(yaml);
		system("cls");
		if (DNSServer == 1)printf("\n已选定：%s\n\n", "OpenDNS");
		else if (DNSServer == 2)printf("\n已选定：%s\n\n", "Google");
		else if (DNSServer == 3)printf("\n已选定：%s\n\n", "Quad9");
		else if (DNSServer == 4)printf("\n已选定：%s\n\n", "Cloudflare");
		else if (DNSServer == 5)printf("\n已选定：%s\n\n", "Quad101");
		else if (DNSServer == 6)printf("\n已选定：%s\n\n", "AdGuard");
		else if (DNSServer == 7)printf("\n已选定：%s\n\n", "NextDNS");
		else printf("\n已选定：%s\n\n", "IIJ");
		if (ADSwitch == 1)printf("%s\n\n","已开启Adblock Plus");
		else if (ADSwitch == 2)printf("%s\n\n", "已开启AdGuard");
		else printf("%s\n\n", "已关闭广告拦截功能");
		if (share == 1) {
			printf("%s\n\n", "已开启局域网共享");
		}
		else {
			printf("%s\n\n", "已关闭局域网共享");
		}
		return 0;
}

int NetFixTool() {
	Reset();
	printf("\nDNS解析服务器已成功恢复初始设置！\n\n");
	return 0;
}

int Reset() {
	system("reg add \"HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\" /v ProxyEnable /t REG_DWORD /d 00000000 /f");
	system("reg add \"HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\" /v ProxyServer /t REG_DWORD /d 00000000 /f");
	system("reg add \"HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\" /v ProxyOverride /t REG_DWORD /d 00000000 /f");
	system("copy /y hosts.bak %windir%\\System32\\drivers\\etc\\hosts");
	system("taskkill /f /im AdGuardHome.exe");
	system("del AdGuardHome.yaml");
	system("rmdir /s/q agh-backup");
	system("netsh interface ip set dns \"以太网\" dhcp");
	system("netsh interface ipv6 set dns \"以太网\" dhcp");
	system("netsh interface ip set dns \"WLAN\" dhcp");
	system("netsh interface ipv6 set dns \"WLAN\" dhcp");
Menu3:system("ipconfig /flushdns");
	system("cls");
	printf("-------------------------------------------------------------------------------------\n");
	printf("-----------------------------------找到的适配器--------------------------------------\n");
	printf("-------------------------------------------------------------------------------------\n");
	system("ipconfig /all | find \"以太网适配器\"");
	system("ipconfig /all | find \"无线局域网适配器\"");
	printf("-------------------------------------------------------------------------------------\n");
	printf("软件已默认恢复了\"以太网\"\"WLAN\"适配器上的DNS，如果仍然无法联网，请恢复hosts!\n");
	printf("如需在其他适配器上恢复默认DNS，请输入适配器名称并回车\n");
	printf("如需关闭本地DNS并恢复默认DNS设置，请直接输入x并按回车：");
	ret = scanf("%s", Adapter);
	if (Adapter[0] == 'x' || Adapter[0] == 'X') {
		printf("\nDNS解析服务器已成功恢复初始设置！\n\n");
		return 0;
	}
	else {
		sprintf(Command, "netsh interface ip set dns \"%s\" dhcp", Adapter);
		system(Command);
		sprintf(Command, "netsh interface ipv6 set dns \"%s\" dhcp", Adapter);
		system(Command);
		goto Menu3;
	}
}

int RunLocalDNSServer() {
	char SystemDir[50];
	printf("正在初始化. . .\n\n");
	sprintf(SystemDir, "%s\\System32\\drivers\\etc\\hosts", getenv("windir"));
	if (fopen(SystemDir, "r") == NULL) {
		SystemHosts = fopen(SystemDir, "w");
		fprintf(SystemHosts, "127.0.0.1 localhost\n");
		fclose(SystemHosts);
	}
	system("copy /y %windir%\\System32\\drivers\\etc\\hosts hosts.bak");
	system("copy /y hosts %windir%\\System32\\drivers\\etc\\hosts");
	system("copy /y index.yaml AdGuardHome.yaml");
	system("reg add \"HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\" /v ProxyEnable /t REG_DWORD /d 00000000 /f");
	system("reg add \"HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\" /v ProxyServer /t REG_DWORD /d 00000000 /f");
	system("reg add \"HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\" /v ProxyOverride /t REG_DWORD /d 00000000 /f");
	printf("\n正在部署DNS解析服务器. . .\n\n");
	system("start "" /min AdGuardHome.exe");
	system("cls");
	printf("正在将DNS解析服务器设置为本地解析（可能会有报错，忽略即可）. . .\n\n");
	system("netsh interface ip set dns \"以太网\" static 127.0.0.1");
	system("netsh interface ipv6 set dns \"以太网\" static ::1");
	system("netsh interface ip set dns \"WLAN\" static 127.0.0.1");
	system("netsh interface ipv6 set dns \"WLAN\" static ::1");
	system("ipconfig /flushdns");
Menu2:system("cls");
	printf("-------------------------------------------------------------------------------------\n");
	printf("------------------------------------DNS部署成功!-------------------------------------\n");
	printf("-------------------------------------------------------------------------------------\n");
	printf("注意：使用防污染DNS期间请不要关闭本窗口及其弹出窗口，后台最小化即可！！！\n");
	printf("如需停止DNS解析请不要直接关闭窗口，否则会导致无法上网！！！\n");
	printf("如果不小心关闭本软件，可以重新打开本软件恢复默认DNS！！！\n");
	printf("-------------------------------------------------------------------------------------\n");
	printf("-----------------------------------找到的适配器--------------------------------------\n");
	printf("-------------------------------------------------------------------------------------\n");
	system("ipconfig /all | find \"以太网适配器\"");
	system("ipconfig /all | find \"无线局域网适配器\"");
	printf("-------------------------------------------------------------------------------------\n");
	printf("软件已默认配置了\"以太网\"\"WLAN\"适配器上的DNS\n");
	printf("如需在其他适配器上配置本地DNS，请输入适配器名称并回车\n");
	printf("如需关闭本地DNS并恢复默认DNS设置，请直接输入x并按回车：");
	ret=scanf("%s",Adapter);
	if (Adapter[0] == 'x'|| Adapter[0] == 'X') {
		Reset();
		printf("\nDNS解析服务器已成功恢复初始设置！\n\n");
		return 0;
	}
	else {
		sprintf(Command, "netsh interface ip set dns \"%s\" static 127.0.0.1", Adapter);
		system(Command);
		sprintf(Command, "netsh interface ipv6 set dns \"%s\" static ::1", Adapter);
		system(Command);
		goto Menu2;
	}
	}
	

int ConfigEditor() {
	printf("请选择修改方式：\n\n1.图形界面（用户名与密码默认均为root）\n\n2.记事本\n\n请输入：");
	ret=scanf("%d", &fixmode);
	if (fixmode == 2) {
		if ((yaml = fopen("index.yaml", "r")) == NULL) {
			Config_gen();
		}
		system("copy /y index.yaml index.yaml.bak");
		system("notepad.exe index.yaml");
		printf("\n请在弹出窗口中修改配置文件后，");
		system("pause");
	}
	else {
		printf("正在准备配置文件. . .\n\n");
		system("copy /y index.yaml index.yaml.bak");
		system("copy /y index.yaml AdGuardHome.yaml");
		printf("正在部署DNS解析服务器. . .\n\n");
		system("start "" /min AdGuardHome.exe");
		system("explorer.exe http://127.0.0.1");
		printf("\n请在弹出窗口中修改配置文件后，");
		system("pause");
		system("taskkill /f /im AdGuardHome.exe");
		system("copy /y AdGuardHome.yaml index.yaml");
		system("del AdGuardHome.yaml");
		system("rmdir /s/q agh-backup");
		system("cls");
	}
	return 0;
}

int ConfigToDefault() {
	if ((bak = fopen("index.yaml.bak", "r")) != NULL){
		printf("软件目录中找到上次的配置备份，请选择恢复模式：\n\n1.恢复到上一次的配置\n\n2.恢复初始状态\n\n请输入：");
		ret=scanf("%d", &fixmode);
		if (fixmode == 1) {
			system("copy /y index.yaml.bak index.yaml");
			printf("\n已成功恢复到上一次的配置！\n");
			return 0;
		}
	}
	system("cls");
	Config_gen();
	printf("\n已成功恢复初始状态！\n");
	return 0;
}

int NSTool() {
	Boot();
	printf("正在初始化. . .\n\n");
	printf("\n正在准备配置文件. . .\n\n");
	system("copy /y index.yaml AdGuardHome.yaml");
	printf("\n正在部署DNS解析服务器. . .\n\n");
	system("start "" /min AdGuardHome.exe");
	system("ipconfig /flushdns");
	NSMenu:system("cls");
	printf("请输入要查询的域名,返回上一级请输入@：\n");
	ret=scanf("%s",domain );
	if (domain[0] == '@') {
		system("taskkill /f /im AdGuardHome.exe");
		system("del AdGuardHome.yaml");
		system("rmdir /s/q agh-backup");
		return 0;
	}
	else {
		sprintf(NSCommand, "nslookup %s 127.0.0.1", domain);
		printf("\n以下为无污染DNS解析结果：\n\n");
		system(NSCommand);
		system("pause");
		goto NSMenu;
	}
	return 0;
}

int Help() {
	printf("正在打开在线帮助. . .\n");
	system("explorer https://hxhgts.ml/AntiDNSPollute/");
	return 0;
}

int Boot() {
	mode = 0;
	system("taskkill /f /im AdGuardHome.exe");
	system("del AdGuardHome.yaml");
	system("rmdir /s/q agh-backup");
	system("cls");
	if ((fopen("hosts", "r")) == NULL) {
		SystemHosts = fopen("hosts", "w");
		fprintf(SystemHosts, "##可以在下面自由添加需要的hosts信息，仅会在模式1下生效!\n");
		fprintf(SystemHosts, "127.0.0.1 localhost\n3.217.204.190 collector.githubapp.com\n151.101.128.133 raw.githubusercontent.com\n\n");
		fclose(SystemHosts);
	}
	if ((AdGuardHome = fopen("AdGuardHome.exe", "r")) == NULL) {
		return 1;
	}
	else {
		if ((yaml = fopen("index.yaml", "r")) == NULL) {
			Config_gen();
			printf("模式1配置文件已生成！\n\n");
		}
		return 0;
	}
}

int FixHosts() {
	printf("正在恢复默认Hosts文件. . .\n\n");
	SystemHosts = fopen("hosts.origin", "w");
	fprintf(SystemHosts, "127.0.0.1 localhost\n");
	fclose(SystemHosts);
	system("copy /y hosts.origin %windir%\\System32\\drivers\\etc\\hosts");
	system("del hosts.origin");
	system("ipconfig /flushdns");
	printf("\n已成功恢复默认Hosts文件！\n\n");
	system("pause");
	system("cls");
	return 0;
}

int Update() {
	Boot();
	int i,j,k;
	if (Boot() != 0) {
		system("cls");
		printf("未在软件目录中发现AdGuardHome引擎，请在官网下载后放置在本软件同一目录下！\n\n");
		system("explorer https://github.com/AdguardTeam/AdGuardHome/releases/latest/download/AdGuardHome_windows_amd64.zip");
	}
	else {
		system("AdGuardHome --version > adguard_current_version.txt");
		system("curl https://api.github.com/repos/AdguardTeam/AdGuardHome/releases/latest | find \"tag_name\" > adguard_source_version.txt");
		system("curl https://api.github.com/repos/HXHGTS/AntiDNSPollute/releases/latest | find \"tag_name\" > anti_source_version.txt");
		system("cls");
		sv = fopen("adguard_source_version.txt", "r");
		ret = fscanf(sv, "  \"tag_name\": \"v%s\",", adguard_source_version);
		fclose(sv);
		sv = fopen("anti_source_version.txt", "r");
		ret = fscanf(sv, "  \"tag_name\": \"v%s\",", anti_source_version);
		fclose(sv);
		cv = fopen("adguard_current_version.txt", "r");
		ret = fscanf(cv, "AdGuard Home, version %s, channel release, arch windows amd64", adguard_current_version);
		fclose(cv);
		for (i = 0; i <= 15; i++) {
			if (adguard_source_version[i] == '\"') {
				adguard_source_version[i] = '\0';
			}
		}
		for (i = 0; i <= 4; i++) {
			if (anti_source_version[i] == '\"') {
				anti_source_version[i] = '\0';
			}
		}
		for (i = 0,j=0; i <= 6; i++) {
			if (adguard_current_version[i] != adguard_source_version[i]) {
				j = j + 1;
			}
		}
		for (i = 0, k = 0; i <= 3; i++) {
			if (anti_current_version[i] != anti_source_version[i]) {
				k = k + 1;
			}
		}
		printf("AdGuardHome当前版本: %s 最新版本: %s \n", adguard_current_version, adguard_source_version);
		if (j != 0) {
			printf("AdGuardHome检测到新版本!\n");
			system("start explorer https://github.com/AdguardTeam/AdGuardHome/releases/latest/download/AdGuardHome_windows_amd64.zip");
		}
		else {
			printf("AdGuardHome已经是最新版本!\n");
		}
		printf("\nAntiDNSPollute当前版本: %s 最新版本: %s \n", anti_current_version, anti_source_version);
		if (k != 0) {
			printf("AntiDNSPollute检测到新版本!\n");
			system("start explorer https://github.com/HXHGTS/AntiDNSPollute/releases/latest/download/AntiDNSPollute.X64.exe");
		}
		else {
			printf("AntiDNSPollute已经是最新版本!\n");
		}
		printf("\n");
		system("pause");
	}
	return 0;
}
