// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef NETDATA_RRDENGINEAPI_H
#define NETDATA_RRDENGINEAPI_H

#include "rrdengine.h"

#define RRDENG_MIN_PAGE_CACHE_SIZE_MB (32)
#define RRDENG_MIN_DISK_SPACE_MB (256)

#define RRDENG_NR_STATS (33)

#define RRDENG_FD_BUDGET_PER_INSTANCE (50)

extern int default_rrdeng_page_cache_mb;
extern int default_rrdeng_disk_quota_mb;

struct rrdeng_region_info {
    time_t start_time;
    int update_every;
    unsigned points;
};

extern void *rrdeng_create_page(struct rrdengine_instance *ctx, uuid_t *id, struct rrdeng_page_descr **ret_descr);
extern void rrdeng_commit_page(struct rrdengine_instance *ctx, struct rrdeng_page_descr *descr,
                               Word_t page_correlation_id);
extern void *rrdeng_get_latest_page(struct rrdengine_instance *ctx, uuid_t *id, void **handle);
extern void *rrdeng_get_page(struct rrdengine_instance *ctx, uuid_t *id, usec_t point_in_time, void **handle);
extern void rrdeng_put_page(struct rrdengine_instance *ctx, void *handle);
extern void rrdeng_store_metric_init(RRDDIM *rd);
extern void rrdeng_store_metric_flush_current_page(RRDDIM *rd);
extern void rrdeng_store_metric_next(RRDDIM *rd, usec_t point_in_time, storage_number number);
extern void rrdeng_store_metric_finalize(RRDDIM *rd);
extern unsigned
    rrdeng_variable_step_boundaries(RRDSET *st, time_t start_time, time_t end_time,
                                    struct rrdeng_region_info **region_info_arrayp, unsigned *max_intervalp);
extern void rrdeng_load_metric_init(RRDDIM *rd, struct rrddim_query_handle *rrdimm_handle,
                                    time_t start_time, time_t end_time);
extern storage_number rrdeng_load_metric_next(struct rrddim_query_handle *rrdimm_handle, time_t *current_time);
extern int rrdeng_load_metric_is_finished(struct rrddim_query_handle *rrdimm_handle);
extern void rrdeng_load_metric_finalize(struct rrddim_query_handle *rrdimm_handle);
extern time_t rrdeng_metric_latest_time(RRDDIM *rd);
extern time_t rrdeng_metric_oldest_time(RRDDIM *rd);
extern void rrdeng_get_33_statistics(struct rrdengine_instance *ctx, unsigned long long *array);

/* must call once before using anything */
extern int rrdeng_init(struct rrdengine_instance **ctxp, char *dbfiles_path, unsigned page_cache_mb,
                       unsigned disk_space_mb);

extern int rrdeng_exit(struct rrdengine_instance *ctx);

#endif /* NETDATA_RRDENGINEAPI_H */